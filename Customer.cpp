#include "Customer.h"
#include "DateUtil.h"
#include <cstring>
#include <iostream>
using namespace std;

Customer::Customer(const char* uname, const char* pwd)
    : User(uname, pwd), accountCount(0) {
    for (int i = 0; i < 5; ++i) accounts[i] = 0;
}

Customer::~Customer() {
    for (int i = 0; i < accountCount; ++i) {
        delete accounts[i];
    }
}

bool Customer::login(const char* uname, const char* pwd) {
    return (strcmp(username, uname) == 0 && strcmp(password, pwd) == 0);
}

void Customer::displayMenu() {
    cout << "Customer Menu for " << username << endl;
    cout << "1. View Accounts\n2. Deposit\n3. Withdraw\n4. Transfer\n5. View Transactions\n6. Exit" << endl;
}

bool Customer::addAccount(Account* acc) {
    if (accountCount < 5) {
        accounts[accountCount++] = acc;
        return true;
    }
    return false;
}

bool Customer::removeAccount(int accNumber) {
    for (int i = 0; i < accountCount; ++i) {
        if (accounts[i] && accounts[i]->getAccountNumber() == accNumber) {
            delete accounts[i];
            for (int j = i; j < accountCount - 1; ++j) {
                accounts[j] = accounts[j + 1];
            }
            accounts[accountCount - 1] = 0;
            --accountCount;
            return true;
        }
    }
    return false;
}

void Customer::deposit(int accNumber, double amount) {
    Account* acc = getAccount(accNumber);
    if (!acc) {
        cout << "Account not found!" << endl;
        return;
    }
    if (amount <= 0) {
        cout << "Amount must be positive!" << endl;
        return;
    }
    acc->deposit(amount);
    char date[20];
    getCurrentDate(date, 20);
    Transaction t(date, "Deposit", amount, accNumber, accNumber);
    acc->addTransaction(t);
    cout << "Deposit successful." << endl;
}

void Customer::withdraw(int accNumber, double amount) {
    Account* acc = getAccount(accNumber);
    if (!acc) {
        cout << "Account not found!" << endl;
        return;
    }
    if (amount <= 0) {
        cout << "Amount must be positive!" << endl;
        return;
    }
    if (!acc->withdraw(amount)) {
        cout << "Insufficient funds!" << endl;
        return;
    }
    char date[20];
    getCurrentDate(date, 20);
    Transaction t(date, "Withdraw", amount, accNumber, accNumber);
    acc->addTransaction(t);
    cout << "Withdrawal successful." << endl;
}

void Customer::transfer(int fromAcc, int toAcc, double amount) {
    Account* from = getAccount(fromAcc);
    Account* to = getAccount(toAcc);
    if (!from) {
        cout << "Source account not found!" << endl;
        return;
    }
    if (!to) {
        cout << "Destination account not found!" << endl;
        return;
    }
    if (amount <= 0) {
        cout << "Amount must be positive!" << endl;
        return;
    }
    if (!from->withdraw(amount)) {
        cout << "Insufficient funds in source account!" << endl;
        return;
    }
    to->deposit(amount);
    char date[20];
    getCurrentDate(date, 20);
    Transaction t(date, "Transfer", amount, fromAcc, toAcc);
    from->addTransaction(t);
    to->addTransaction(t);
    cout << "Transfer successful." << endl;
}

void Customer::viewAccounts() {
    for (int i = 0; i < accountCount; ++i) {
        if (accounts[i]) accounts[i]->displayDetails();
    }
}

void Customer::printTransactionHistory() {
    for (int i = 0; i < accountCount; ++i) {
        if (accounts[i]) accounts[i]->printTransactionHistory();
    }
}

Account* Customer::getAccount(int accNumber) {
    // Only return accounts owned by this customer
    for (int i = 0; i < accountCount; ++i) {
        if (accounts[i] && accounts[i]->getAccountNumber() == accNumber) {
            return accounts[i];
        }
    }
    return 0;
}

int Customer::getAccountCount() const {
    return accountCount;
} 