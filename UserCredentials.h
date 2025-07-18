#ifndef USERCREDENTIALS_H
#define USERCREDENTIALS_H

struct UserCredentials {
    char username[50];
    char password[50];
    char role[20];
};

int loadUsers(const char* filename, UserCredentials users[], int maxUsers);
int saveUsers(const char* filename, UserCredentials users[], int userCount);

#endif // USERCREDENTIALS_H 