#include "LoanAccount.h"
#include "DateUtil.h"
#include <iostream>
using namespace std;

LoanAccount::LoanAccount(int accNo, const char* name, double loanAmount)
    : Account(accNo, name, loanAmount) {}

LoanAccount::~LoanAccount() {}

void LoanAccount::deposit(double amount) {
    if (amount > 0) {
        balance -= amount;
        if (balance < 0) balance = 0;
        char date[20];
        getCurrentDate(date, 20);
        Transaction t(date, "Repay", amount, accountNumber, accountNumber);
        addTransaction(t);
    }
}

bool LoanAccount::withdraw(double amount) {
    if (amount > 0) {
        balance += amount;
        char date[20];
        getCurrentDate(date, 20);
        Transaction t(date, "Loan", amount, accountNumber, accountNumber);
        addTransaction(t);
        return true;
    }
    return false;
}

void LoanAccount::displayDetails() const {
    cout << "[Loan Account]" << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Holder Name: " << holderName << endl;
    cout << "Loan Remaining: $" << balance << endl;
}

double LoanAccount::getBalance() const {
    return balance;
}

void LoanAccount::printTransactionHistory() const {
    Account::printTransactionHistory();
}

void LoanAccount::applyMonthlyUpdate() {
    double interest = balance * 0.10;
    balance += interest;
    char date[20];
    getCurrentDate(date, 20);
    Transaction t(date, "Interest", interest, accountNumber, accountNumber);
    addTransaction(t);
    cout << "[LoanAccount] Interest accrued: $" << interest << " to account " << accountNumber << endl;
} 