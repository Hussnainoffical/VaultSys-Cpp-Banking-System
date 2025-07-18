#include "Account.h"
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

Account::Account(int accNo, const char* name, double initialBalance)
    : accountNumber(accNo), balance(initialBalance), transactionCount(0) {
    strncpy(holderName, name, sizeof(holderName) - 1);
    holderName[sizeof(holderName) - 1] = '\0';
}

Account::~Account() {}

int Account::getAccountNumber() const {
    return accountNumber;
}

const char* Account::getHolderName() const {
    return holderName;
}

void Account::addTransaction(const Transaction& t) {
    if (transactionCount < 20) {
        transactions[transactionCount++] = t;
    }
}

void Account::printTransactionHistory() const {
    cout << "Transaction History for Account " << accountNumber << ":" << endl;
    for (int i = 0; i < transactionCount; ++i) {
        transactions[i].print();
    }
}

void Account::saveToFile(const char* filename) const {
    ofstream fout(filename, ios::app);
    if (fout) {
        fout << accountNumber << ',' << holderName << ',' << balance << endl;
        fout.close();
    }
}

void Account::loadFromFile(const char* filename, int accNumber) {
    ifstream fin(filename);
    if (!fin) return;
    char line[256];
    while (fin.getline(line, sizeof(line))) {
        char* token = strtok(line, ",");
        if (!token) continue;
        int fileAccNo = atoi(token);
        if (fileAccNo == accNumber) {
            token = strtok(0, ",");
            if (token) strncpy(holderName, token, sizeof(holderName) - 1);
            holderName[sizeof(holderName) - 1] = '\0';
            token = strtok(0, ",");
            if (token) balance = atof(token);
            break;
        }
    }
    fin.close();
}

void Account::onMonthPassed() {
    applyMonthlyUpdate();
}

int Account::getTransactionCount() const {
    return transactionCount;
}

const Transaction* Account::getTransactions() const {
    return transactions;
} 