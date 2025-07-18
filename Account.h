#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Transaction.h"
#include "MonthlyObserver.h"

class Account : public MonthlyObserver {
protected:
    int accountNumber;
    char holderName[100];
    double balance;
    Transaction transactions[20]; // Transaction history
    int transactionCount;
public:
    Account(int accNo, const char* name, double initialBalance);
    virtual ~Account();
    virtual void deposit(double amount) = 0; // Must be positive
    virtual bool withdraw(double amount) = 0; // Only if sufficient funds
    virtual void displayDetails() const = 0;
    virtual double getBalance() const = 0;
    int getAccountNumber() const;
    const char* getHolderName() const;
    void addTransaction(const Transaction& t);
    void printTransactionHistory() const;
    virtual void saveToFile(const char* filename) const;
    virtual void loadFromFile(const char* filename, int accNumber);
    virtual void applyMonthlyUpdate() = 0;
    virtual void onMonthPassed();
    int getTransactionCount() const;
    const Transaction* getTransactions() const;
};

#endif // ACCOUNT_H 