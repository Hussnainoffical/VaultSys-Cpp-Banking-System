#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Customer.h"

class Admin : public User {
public:
    Admin(const char* uname, const char* pwd);
    virtual ~Admin();
    virtual bool login(const char* uname, const char* pwd);
    virtual void displayMenu();
    void createAccountForCustomer(Customer* customer, Account* acc);
    void deleteAccountForCustomer(Customer* customer, int accNumber);
    void viewAllCustomers(Customer* customers[], int customerCount);
};

#endif // ADMIN_H 