#include "DataIO.h"
#include "AccountFactory.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "LoanAccount.h"
#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;

// Helper to find or create a customer by name
Customer* findOrCreateCustomer(const char* name, Customer* customers[], int* customerCount, int maxCustomers) {
    for (int i = 0; i < *customerCount; ++i) {
        if (strcmp(customers[i]->getUsername(), name) == 0) return customers[i];
    }
    if (*customerCount < maxCustomers) {
        Customer* c = new Customer(name, "default");
        customers[(*customerCount)++] = c;
        return c;
    }
    return 0;
}

int loadAccounts(const char* filename, Customer* customers[], int* customerCount, int maxCustomers) {
    ifstream fin(filename);
    if (!fin) return 0;
    char line[256];
    int accLoaded = 0;
    while (fin.getline(line, sizeof(line))) {
        if (strlen(line) < 3) continue;
        char* token = strtok(line, ",");
        if (!token) continue;
        int accNo = atoi(token);
        token = strtok(0, ",");
        if (!token) continue;
        char type[20]; strncpy(type, token, 19); type[19] = '\0';
        token = strtok(0, ",");
        if (!token) continue;
        char holder[100]; strncpy(holder, token, 99); holder[99] = '\0';
        token = strtok(0, ",");
        if (!token) continue;
        double bal = atof(token);
        Account* acc = AccountFactory::createAccount(type, holder, accNo, bal);
        if (!acc) continue;
        Customer* cust = findOrCreateCustomer(holder, customers, customerCount, maxCustomers);
        if (cust) cust->addAccount(acc);
        accLoaded++;
    }
    fin.close();
    return accLoaded;
}

int saveAccounts(const char* filename, Customer* customers[], int customerCount) {
    ofstream fout(filename);
    if (!fout) return 0;
    for (int i = 0; i < customerCount; ++i) {
        Customer* cust = customers[i];
        for (int j = 0; j < cust->getAccountCount(); ++j) {
            Account* acc = cust->getAccount(j);
            if (acc) {
                fout << acc->getAccountNumber() << ',';
                if (dynamic_cast<SavingsAccount*>(acc)) fout << "savings";
                else if (dynamic_cast<CurrentAccount*>(acc)) fout << "current";
                else if (dynamic_cast<LoanAccount*>(acc)) fout << "loan";
                else fout << "unknown";
                fout << ',' << acc->getHolderName() << ',' << acc->getBalance() << endl;
            }
        }
    }
    fout.close();
    return 1;
}

int loadTransactions(const char* filename, Customer* customers[], int customerCount) {
    ifstream fin(filename);
    if (!fin) return 0;
    char line[256];
    int txLoaded = 0;
    while (fin.getline(line, sizeof(line))) {
        if (strlen(line) < 3) continue;
        char* token = strtok(line, ",");
        if (!token) continue;
        int accNo = atoi(token);
        token = strtok(0, ",");
        if (!token) continue;
        char date[20]; strncpy(date, token, 19); date[19] = '\0';
        token = strtok(0, ",");
        if (!token) continue;
        char type[15]; strncpy(type, token, 14); type[14] = '\0';
        token = strtok(0, ",");
        if (!token) continue;
        double amt = atof(token);
        token = strtok(0, ",");
        int fromAcc = token ? atoi(token) : 0;
        token = strtok(0, ",");
        int toAcc = token ? atoi(token) : 0;
        // Find the account
        for (int i = 0; i < customerCount; ++i) {
            Customer* cust = customers[i];
            for (int j = 0; j < cust->getAccountCount(); ++j) {
                Account* acc = cust->getAccount(j);
                if (acc && acc->getAccountNumber() == accNo) {
                    Transaction t(date, type, amt, fromAcc, toAcc);
                    acc->addTransaction(t);
                    txLoaded++;
                    break;
                }
            }
        }
    }
    fin.close();
    return txLoaded;
}

int saveTransactions(const char* filename, Customer* customers[], int customerCount) {
    ofstream fout(filename);
    if (!fout) return 0;
    for (int i = 0; i < customerCount; ++i) {
        Customer* cust = customers[i];
        for (int j = 0; j < cust->getAccountCount(); ++j) {
            Account* acc = cust->getAccount(j);
            if (acc) {
                const Transaction* txs = acc->getTransactions();
                int txCount = acc->getTransactionCount();
                for (int k = 0; k < txCount; ++k) {
                    fout << acc->getAccountNumber() << ','
                         << txs[k].getDate() << ','
                         << txs[k].getType() << ','
                         << txs[k].getAmount() << ','
                         << txs[k].getFromAccount() << ','
                         << txs[k].getToAccount() << endl;
                }
            }
        }
    }
    fout.close();
    return 1;
} 