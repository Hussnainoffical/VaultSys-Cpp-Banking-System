#ifndef LOANACCOUNT_H
#define LOANACCOUNT_H

#include "Account.h"

// LoanAccount derived from Account
class LoanAccount : public Account {
public:
    LoanAccount(int accNo, const char* name, double loanAmount);
    virtual ~LoanAccount();

    virtual void deposit(double amount);      // Repay loan
    virtual bool withdraw(double amount);     // Take more loan (increase balance)
    virtual void displayDetails() const;
    virtual double getBalance() const;
    virtual void printTransactionHistory() const;
    virtual void applyMonthlyUpdate();
};

#endif // LOANACCOUNT_H 