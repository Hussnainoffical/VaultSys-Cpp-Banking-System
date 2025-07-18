#include "Transaction.h"
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

Transaction::Transaction() {
    date[0] = '\0';
    type[0] = '\0';
    amount = 0;
    fromAccount = 0;
    toAccount = 0;
}

Transaction::Transaction(const char* d, const char* t, double amt, int fromAcc, int toAcc) {
    strncpy(date, d, sizeof(date) - 1);
    date[sizeof(date) - 1] = '\0';
    strncpy(type, t, sizeof(type) - 1);
    type[sizeof(type) - 1] = '\0';
    amount = amt;
    fromAccount = fromAcc;
    toAccount = toAcc;
}

void Transaction::set(const char* d, const char* t, double amt, int fromAcc, int toAcc) {
    strncpy(date, d, sizeof(date) - 1);
    date[sizeof(date) - 1] = '\0';
    strncpy(type, t, sizeof(type) - 1);
    type[sizeof(type) - 1] = '\0';
    amount = amt;
    fromAccount = fromAcc;
    toAccount = toAcc;
}

void Transaction::print() const {
    cout << date << " | " << type << " | $" << amount << " | From: " << fromAccount << " | To: " << toAccount << endl;
}

void Transaction::saveToFile(const char* filename) const {
    ofstream fout(filename, ios::app);
    if (fout) {
        fout << date << ',' << type << ',' << amount << ',' << fromAccount << ',' << toAccount << endl;
        fout.close();
    }
}

bool Transaction::loadFromFile(const char* filename, int index) {
    ifstream fin(filename);
    if (!fin) return false;
    char line[256];
    int count = 0;
    while (fin.getline(line, sizeof(line))) {
        if (count == index) {
            char* token = strtok(line, ",");
            if (!token) break;
            strncpy(date, token, sizeof(date) - 1);
            date[sizeof(date) - 1] = '\0';
            token = strtok(0, ",");
            if (!token) break;
            strncpy(type, token, sizeof(type) - 1);
            type[sizeof(type) - 1] = '\0';
            token = strtok(0, ",");
            if (!token) break;
            amount = atof(token);
            token = strtok(0, ",");
            if (!token) break;
            fromAccount = atoi(token);
            token = strtok(0, ",");
            if (!token) break;
            toAccount = atoi(token);
            fin.close();
            return true;
        }
        count++;
    }
    fin.close();
    return false;
}

const char* Transaction::getType() const { return type; }
double Transaction::getAmount() const { return amount; }
int Transaction::getFromAccount() const { return fromAccount; }
int Transaction::getToAccount() const { return toAccount; }
const char* Transaction::getDate() const { return date; } 