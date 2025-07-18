#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
public:
    SavingsAccount(int accNo, const char* name, double initialBalance);
    virtual ~SavingsAccount();
    virtual void deposit(double amount);
    virtual bool withdraw(double amount);
    virtual void displayDetails() const;
    virtual double getBalance() const;
    virtual void printTransactionHistory() const;
    virtual void applyMonthlyUpdate();
};

#endif // SAVINGSACCOUNT_H 