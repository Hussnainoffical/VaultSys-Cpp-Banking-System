#ifndef DATAIO_H
#define DATAIO_H

#include "Customer.h"
#include "Account.h"

int loadAccounts(const char* filename, Customer* customers[], int* customerCount, int maxCustomers);
int saveAccounts(const char* filename, Customer* customers[], int customerCount);
int loadTransactions(const char* filename, Customer* customers[], int customerCount);
int saveTransactions(const char* filename, Customer* customers[], int customerCount);

#endif // DATAIO_H 