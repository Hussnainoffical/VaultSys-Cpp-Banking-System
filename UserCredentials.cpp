#include "UserCredentials.h"
#include <fstream>
#include <cstring>
using namespace std;

int loadUsers(const char* filename, UserCredentials users[], int maxUsers) {
    ifstream fin(filename);
    if (!fin) return 0;
    char line[128];
    int count = 0;
    while (fin.getline(line, sizeof(line)) && count < maxUsers) {
        if (strlen(line) < 3) continue;
        char* token = strtok(line, ",");
        if (!token) continue;
        strncpy(users[count].username, token, 49); users[count].username[49] = '\0';
        token = strtok(0, ",");
        if (!token) continue;
        strncpy(users[count].password, token, 49); users[count].password[49] = '\0';
        token = strtok(0, ",");
        if (!token) continue;
        strncpy(users[count].role, token, 19); users[count].role[19] = '\0';
        ++count;
    }
    fin.close();
    return count;
}

int saveUsers(const char* filename, UserCredentials users[], int userCount) {
    ofstream fout(filename);
    if (!fout) return 0;
    for (int i = 0; i < userCount; ++i) {
        fout << users[i].username << ',' << users[i].password << ',' << users[i].role << endl;
    }
    fout.close();
    return 1;
} 