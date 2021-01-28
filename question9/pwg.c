#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "check_pass.h"

// programme qui permet aux utilisateurs des groupes 'groupe_a' et 'groupe_b' de créer un mdp ou de le modifier
// en les cryptant et en mettant leur hash dans le fichier passwd
// admin ne pourra plus les lire en clair
int main(){
    printf("id utilisateur -> %d\n", getuid());
    int res = createOrModifyPasswd();
    if(res == 1){
        printf("nouvel utilisateur inscrit\n");
    }
    else if(res == 2){
        printf("mot de passe modifié\n");
    }
    else if(res == -1){
        printf("erreur, mauvais mdp donné\n");
    }
    else{
        printf("erreur\n");
    }
}