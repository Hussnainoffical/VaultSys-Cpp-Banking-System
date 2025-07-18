#ifndef TRANSACTION_H
#define TRANSACTION_H

class Transaction {
private:
    char date[20];      // e.g. "2024-06-01"
    char type[15];      // Deposit, Withdraw, Transfer
    double amount;
    int fromAccount;
    int toAccount;
public:
    Transaction();
    Transaction(const char* date, const char* type, double amount, int fromAcc, int toAcc);
    void set(const char* date, const char* type, double amount, int fromAcc, int toAcc);
    void print() const;
    void saveToFile(const char* filename) const;
    bool loadFromFile(const char* filename, int index); // Load nth transaction from file
    const char* getType() const;
    double getAmount() const;
    int getFromAccount() const;
    int getToAccount() const;
    const char* getDate() const;
};

#endif // TRANSACTION_H 