#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "check_pass.h"

int main(int argc, char *argv[]){
    FILE *f;
    printf("Fichier à supprimer: %s\n", argv[1]);
    printf("- EUID : %d\n", geteuid());
    printf("- EGID : %d\n", getegid());

    if(access(argv[1], W_OK) != 0){
        printf("pas autorisé à supprimer ce fichier\n");
    }
    else{
        printf("autorisé à supprimer\n");
        printf("Entrez votre mot de passe:\n");
        char mdp[100];
        scanf("%s", mdp);
        //printf("mdp entré: %s\n", mdp);
        //printf("longueur %ld\n", strlen(mdp));

        int res = checkPassword(mdp);

        if(res != 1){
            printf("Erreur, mauvais mdp\n");
        }
        else{
            printf("Mdp correct\n");
            if(remove(argv[1]) == 0){
                printf("Fichier supprimé!\n");
            }
            else{
                printf("Erreur supression\n");
            }
        }
    }

    // f = fopen(argv[1], "r");

    // if(f == NULL)
    //     perror("Cannot open file on read mode");
    // else {
    //     printf("File open correctly on read mode\n");
    // }
    return 0;
}