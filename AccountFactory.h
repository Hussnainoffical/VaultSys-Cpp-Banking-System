#ifndef ACCOUNTFACTORY_H
#define ACCOUNTFACTORY_H

#include "Account.h"

class AccountFactory {
public:
    static Account* createAccount(const char* type, const char* name, int accNumber, double initialAmount);
};

#endif // ACCOUNTFACTORY_H 