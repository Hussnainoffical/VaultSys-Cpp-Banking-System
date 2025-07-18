#include "SavingsAccount.h"
#include "DateUtil.h"
#include <iostream>
using namespace std;

SavingsAccount::SavingsAccount(int accNo, const char* name, double initialBalance)
    : Account(accNo, name, initialBalance) {}

SavingsAccount::~SavingsAccount() {}

void SavingsAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        char date[20];
        getCurrentDate(date, 20);
        Transaction t(date, "Deposit", amount, accountNumber, accountNumber);
        addTransaction(t);
    }
}

bool SavingsAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        char date[20];
        getCurrentDate(date, 20);
        Transaction t(date, "Withdraw", amount, accountNumber, accountNumber);
        addTransaction(t);
        return true;
    }
    return false;
}

void SavingsAccount::displayDetails() const {
    cout << "[Savings Account]" << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Holder Name: " << holderName << endl;
    cout << "Balance: $" << balance << endl;
}

double SavingsAccount::getBalance() const {
    return balance;
}

void SavingsAccount::printTransactionHistory() const {
    Account::printTransactionHistory();
}

void SavingsAccount::applyMonthlyUpdate() {
    double interest = balance * 0.03;
    balance += interest;
    char date[20];
    getCurrentDate(date, 20);
    Transaction t(date, "Interest", interest, accountNumber, accountNumber);
    addTransaction(t);
    cout << "[SavingsAccount] Interest applied: $" << interest << " to account " << accountNumber << endl;
} 