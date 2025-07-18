#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "Account.h"

class Customer : public User {
private:
    Account* accounts[5];
    int accountCount;
public:
    Customer(const char* uname, const char* pwd);
    virtual ~Customer();
    virtual bool login(const char* uname, const char* pwd);
    virtual void displayMenu();
    bool addAccount(Account* acc);
    bool removeAccount(int accNumber);
    void deposit(int accNumber, double amount);
    void withdraw(int accNumber, double amount);
    void transfer(int fromAcc, int toAcc, double amount);
    void viewAccounts();
    void printTransactionHistory();
    Account* getAccount(int accNumber);
    int getAccountCount() const;
};

#endif // CUSTOMER_H 