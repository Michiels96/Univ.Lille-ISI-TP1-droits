#ifndef CheckPass
#define CheckPass

#define MAX_LENGTH 50


typedef struct User User;

struct User{
    int userID;
    char password[MAX_LENGTH];
};

void removeBackSlashN(char *string);
void createLocalUserDB(int nbUsers, char existingArray[nbUsers][MAX_LENGTH], User *resultArray);
int checkPassword(char *givenPass);
int init();
int createOrModifyPasswd();
void rewriteFile();
void getCryptedPass(char *givenPass);
int passwordCmp(char *givenPass, char *recordedPass);

#endif