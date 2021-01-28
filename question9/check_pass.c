#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "check_pass.h"

#include <time.h>
#include <crypt.h>

char *passwdFilePath = "/home/admin/passwd";
int nbUsers;
FILE *f;
User *usersDB;


void removeBackSlashN(char *string){
    for(int i = 0;i < strlen(string); i++){
        if(string[i] == '\n'){
            string[i] = '\0';
        }
    }
}

void createLocalUserDB(int nbUsers, char existingArray[nbUsers][MAX_LENGTH], User *resultArray){
    //int users = sizeof(resultArray);
    //printf("nb %d\n", users);
    for(int i =0; i < nbUsers; i++){
        User user;
        char *e;
        e = strchr(existingArray[i], ':');
        int index = (int)(e - existingArray[i]);
        char *username = (char *)calloc(index, sizeof(char));
        for(int j = 0; j < index; j++){
            username[j] = existingArray[i][j];
        }
        user.userID = atoi(username);
        //printf("%s\n", user.username);
        char *pass = strchr(existingArray[i], ':');
        memmove(pass, pass+1, strlen(pass));
        strcpy(user.password, pass);
        //printf("%s\n", user.password);
        resultArray[i] = user;
    }
}

int init(){
    //printf("mdp donné -> %s\n", givenPass);
    // access ne prends pas en compte le flag set-user-id
    // if(access(passwdFilePath, R_OK) != 0){
    //     printf("Pas autorisé à lire le fichier %s\n", passwdFilePath);
    // }
    
    //printf("Autorisé à lire le fichier %s\n", passwdFilePath);
    //FILE *f;
    f = fopen(passwdFilePath, "r");
    if(f == NULL){
        perror("Cannot open file on read mode");
        return -1;
    }
    else {
        char *buffer = (char *) malloc(MAX_LENGTH);
        //count users part
        int i = 0;
        while(!feof(f)){
            fgets(buffer, MAX_LENGTH, f);
            if(ferror(f)){
                fprintf(stderr, "Reading error with code %d\n", errno);
                break;
            }
            i++;
        }
        nbUsers = i-1;
        if(nbUsers > 0){
            char usersWithPass[nbUsers][MAX_LENGTH];
            rewind(f);
            i = 0;
            while(i < nbUsers){
                fgets(usersWithPass[i], MAX_LENGTH, f);
                if(ferror(f)){
                    fprintf(stderr, "Reading error with code %d\n", errno);
                    break;
                }
                i++;
            }
            for(int i = 0;i < nbUsers; i++){
                removeBackSlashN(usersWithPass[i]);
            }
            usersDB = calloc(nbUsers, sizeof(User));
            createLocalUserDB(nbUsers, usersWithPass, usersDB);
        }
    }
    return 0;
}


int checkPassword(char *givenPass){
    if(init() == 0){
        for(int i = 0; i < nbUsers; i++){
            printf("utilisateur %d:\n\tid: %d\n\tmdp: %s\n", i, usersDB[i].userID, usersDB[i].password);
            if(usersDB[i].userID == getuid()){
                if(strcmp(usersDB[i].password, givenPass) == 0){
                    return 1;
                }
            }
        }
        fclose(f);
    }
    return 0;
}

void rewriteFile(){
    fclose(f);
    f = fopen(passwdFilePath, "w");
    char bufferId[80];
    for(int i = 0; i < nbUsers; i++){
        sprintf(bufferId, "%d", usersDB[i].userID);
        int id = strlen(bufferId);
        int buffSize = id+1+strlen(usersDB[i].password);
        char buffer[buffSize];
        sprintf(buffer, "%d", usersDB[i].userID);
        strcat(buffer, ":");
        strcat(buffer, usersDB[i].password);
        strcat(buffer, "\n");
        fputs(buffer, f);
    }
}

int createOrModifyPasswd(){
    if(init() == 0){
        //verify if user is present in passwd
        int userPresent = 0;
        for(int i = 0; i < nbUsers; i++){
            //printf("utilisateur %d:\n\tid: %d\n\tmdp: %s\n", i, usersDB[i].userID, usersDB[i].password);
            if(usersDB[i].userID == getuid()){
                printf("utilisateur présent \n");
                userPresent = 1;
                printf("Entrez votre mot de passe actuel:\n");
                char mdp[100];
                scanf("%s", mdp);
                //vérification si les mdp sont les memes
                //getCryptedPass(mdp);
                if(passwordCmp(mdp, usersDB[i].password) == 0){
                    return -1;
                }
                
                /*
                printf("ici %s\n", mdp);
                if(strcmp(mdp, usersDB[i].password) != 0){
                    return -1;
                }
                */
                // maj. du nouveau mdp
                printf("Entrez votre Nouveau mot de passe:\n");
                scanf("%s", mdp);
                strcpy(usersDB[i].password, mdp);

                //char *cryptedPass;
                getCryptedPass(usersDB[i].password);
                printf("ici %s\n", usersDB[i].password);
                rewriteFile();
                return 2;
            }
        }

        if(userPresent == 0){
            // new user
            printf("\tNouvel utilisateur\n");
            fclose(f);
            f = fopen(passwdFilePath, "a");
            if(f == NULL){
                perror("Cannot open file on read mode");
                return -1;
            }
            else {
                printf("Entrez votre nouveau mot de passe:\n");
                char mdp[100];
                scanf("%s", mdp);
                getCryptedPass(mdp);
                char bufferId[80];
                sprintf(bufferId, "%d", getuid());
                int id = strlen(bufferId);
                int buffSize = id+1+strlen(mdp);
                char buffer[buffSize];
                strcat(buffer, bufferId);
                strcat(buffer, ":");
                strcat(buffer, mdp);
                strcat(buffer, "\n");
                fputs(buffer, f);
                return 1;
            }
        }
        fclose(f);
    }
    return 0;
}

void getCryptedPass(char *givenPass){
    unsigned long seed[2];
    char salt[] = "$1$........";
    const char *const seedchars = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char *password;
    int i;
    
    /* Generate a (not very) random seed.  
        You should do it better than this... */
    seed[0] = time(NULL);
    seed[1] = getpid() ^ (seed[0] >> 14 & 0x30000);
    
    /* Turn it into printable characters from `seedchars'. */
    for (i = 0; i < 8; i++){
        salt[3+i] = seedchars[(seed[i/5] >> (i%5)*6) & 0x3f];
    }
    
    /* Read in the user's password and encrypt it. */
    password = crypt(givenPass, salt);
    strcpy(givenPass, password);
    
    /* Print the results. */
    //puts(cryptedPass);
}

int passwordCmp(char *givenPass, char *recordedPass){
    /* Hashed form of "GNU libc manual". */
    //const char *const pass = "$1$/iSaq7rB$EoUw5jJPPvAPECNaaWzMK/";

    char *result;
    int ok;
    
    /* Read in the user's password and encrypt it,
        passing the expected password in as the salt. */
    result = crypt(givenPass, recordedPass);

    /* Test the result. */
    ok = strcmp (result, recordedPass) == 0;

    puts(ok ? "Access granted." : "Access denied.");
    return ok;
}