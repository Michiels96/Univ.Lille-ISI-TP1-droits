#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "check_pass.h"




void removeBackSlashN(char *string){
    for(int i = 0;i < strlen(string); i++){
        if(string[i] == '\n'){
            string[i] = '\0';
        }
    }
}

void createLocalUserDB(int nbUsers, char existingArray[nbUsers][MAX_LENGTH], User *resultArray){
    int users = sizeof(resultArray);
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
        strcpy(user.username, username);
        //printf("%s\n", user.username);
        char *pass = strchr(existingArray[i], ':');
        memmove(pass, pass+1, strlen(pass));
        strcpy(user.password, pass);
        //printf("%s\n", user.password);
        resultArray[i] = user;
    }
}

int checkPassword(char *givenPass){
    //printf("mdp donné -> %s\n", givenPass);
    char *passwdFilePath = "/home/admin/passwd";
    // access ne prends pas en compte le flag set-user-id
    // if(access(passwdFilePath, R_OK) != 0){
    //     printf("Pas autorisé à lire le fichier %s\n", passwdFilePath);
    // }
    
    //printf("Autorisé à lire le fichier %s\n", passwdFilePath);
    FILE *f;
    f = fopen(passwdFilePath, "r");

    if(f == NULL)
        perror("Cannot open file on read mode");
    else {
        char *buffer = (char *) malloc(MAX_LENGTH);

        //count users part
        int i = 0;
        while(!feof(f)){
            fgets(buffer, MAX_LENGTH, f);
            if (ferror(f)){
                fprintf(stderr, "Reading error with code %d\n", errno);
                break;
            }
            i++;
        }
        int nbUsers = i-1;
        char usersWithPass[nbUsers][MAX_LENGTH];
        rewind(f);
        i = 0;
        while(i < nbUsers){
            fgets(usersWithPass[i], MAX_LENGTH, f);
            if (ferror(f)){
                fprintf(stderr, "Reading error with code %d\n", errno);
                break;
            }
            i++;
        }
        for(int i = 0;i < nbUsers; i++){
            removeBackSlashN(usersWithPass[i]);
        }
        User usersDB[nbUsers];
        createLocalUserDB(nbUsers, usersWithPass, usersDB);
        for(int i = 0; i < nbUsers; i++){
            //if(strcmp(usersDB[i].username, ) == 0){
                if(strcmp(usersDB[i].password, givenPass) == 0){
                    return 1;
                }
            //}
        }
        fclose(f);
    }
    return 0;
}