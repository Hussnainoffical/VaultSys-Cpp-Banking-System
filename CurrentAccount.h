#ifndef CURRENTACCOUNT_H
#define CURRENTACCOUNT_H

#include "Account.h"

class CurrentAccount : public Account {
public:
    CurrentAccount(int accNo, const char* name, double initialBalance);
    virtual ~CurrentAccount();
    virtual void deposit(double amount);
    virtual bool withdraw(double amount);
    virtual void displayDetails() const;
    virtual double getBalance() const;
    virtual void printTransactionHistory() const;
    virtual void applyMonthlyUpdate();
};

#endif // CURRENTACCOUNT_H 