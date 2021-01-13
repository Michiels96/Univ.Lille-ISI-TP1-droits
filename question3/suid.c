#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *f;

    printf("Affichage des id du programme\n");
    printf("- EUID : %d\n", geteuid());
    printf("- EGID : %d\n", getegid());
    printf("- RUID : %d\n", getuid());
    printf("- RGID : %d\n", getgid());

    f = fopen("../mydir/data.txt", "r");

    if(f == NULL)
        perror("Cannot open file on read mode");
    else {
        printf("File open correctly on read mode\n");
    }
        
    return 0;
}
