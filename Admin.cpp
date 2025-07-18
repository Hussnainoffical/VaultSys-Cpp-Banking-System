#include "Admin.h"
#include <cstring>
#include <iostream>
using namespace std;

Admin::Admin(const char* uname, const char* pwd) : User(uname, pwd) {}

Admin::~Admin() {}

bool Admin::login(const char* uname, const char* pwd) {
    return (strcmp(username, uname) == 0 && strcmp(password, pwd) == 0);
}

void Admin::displayMenu() {
    cout << "Admin Menu for " << username << endl;
    cout << "1. Create Account for Customer\n2. Delete Account for Customer\n3. View All Customers\n4. Exit" << endl;
}

void Admin::createAccountForCustomer(Customer* customer, Account* acc) {
    if (customer && acc) {
        customer->addAccount(acc);
    }
}

void Admin::deleteAccountForCustomer(Customer* customer, int accNumber) {
    if (customer) {
        customer->removeAccount(accNumber);
    }
}

void Admin::viewAllCustomers(Customer* customers[], int customerCount) {
    for (int i = 0; i < customerCount; ++i) {
        if (customers[i]) {
            cout << "Customer: " << customers[i]->getUsername() << endl;
            customers[i]->viewAccounts();
        }
    }
} 