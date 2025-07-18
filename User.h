#ifndef USER_H
#define USER_H

class User {
protected:
    char username[50];
    char password[50];
public:
    User(const char* uname, const char* pwd);
    virtual ~User();
    virtual bool login(const char* uname, const char* pwd) = 0;
    virtual void displayMenu() = 0;
    const char* getUsername() const;
};

#endif // USER_H 