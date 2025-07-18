#include "User.h"
#include <cstring>
using namespace std;

User::User(const char* uname, const char* pwd) {
    strncpy(username, uname, sizeof(username) - 1);
    username[sizeof(username) - 1] = '\0';
    strncpy(password, pwd, sizeof(password) - 1);
    password[sizeof(password) - 1] = '\0';
}

User::~User() {}

const char* User::getUsername() const {
    return username;
} 