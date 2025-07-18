#include "AccountFactory.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "LoanAccount.h"
#include <cstring>

Account* AccountFactory::createAccount(const char* type, const char* name, int accNumber, double initialAmount) {
    if (strcmp(type, "savings") == 0) {
        return new SavingsAccount(accNumber, name, initialAmount);
    } else if (strcmp(type, "current") == 0) {
        return new CurrentAccount(accNumber, name, initialAmount);
    } else if (strcmp(type, "loan") == 0) {
        return new LoanAccount(accNumber, name, initialAmount);
    }
    return 0;
} 