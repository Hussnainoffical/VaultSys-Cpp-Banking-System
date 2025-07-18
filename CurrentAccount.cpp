#include "CurrentAccount.h"
#include "DateUtil.h"
#include <iostream>
using namespace std;

// Constructor
CurrentAccount::CurrentAccount(int accNo, const char* name, double initialBalance)
    : Account(accNo, name, initialBalance) {}

// Destructor
CurrentAccount::~CurrentAccount() {}

// Deposit money
void CurrentAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        // Record transaction
        char date[20];
        getCurrentDate(date, 20);
        Transaction t(date, "Deposit", amount, accountNumber, accountNumber);
        addTransaction(t);
    }
}

// Withdraw money (no overdraft allowed)
bool CurrentAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        // Record transaction
        char date[20];
        getCurrentDate(date, 20);
        Transaction t(date, "Withdraw", amount, accountNumber, accountNumber);
        addTransaction(t);
        return true;
    }
    return false;
}

// Display account details
void CurrentAccount::displayDetails() const {
    cout << "[Current Account]" << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Holder Name: " << holderName << endl;
    cout << "Balance: $" << balance << endl;
}

// Get current balance
double CurrentAccount::getBalance() const {
    return balance;
}

void CurrentAccount::printTransactionHistory() const {
    Account::printTransactionHistory();
}

void CurrentAccount::applyMonthlyUpdate() {
    cout << "[CurrentAccount] No interest applied for account " << accountNumber << endl;
} 