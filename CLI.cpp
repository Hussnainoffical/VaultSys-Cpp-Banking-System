#include "CLI.h"
#include <iostream>
#include <cstring>
#include "AccountFactory.h"
using namespace std;

void showMainMenu() {
    cout << "\n=== Welcome to BankPro! ===" << endl;
    cout << "1. Login" << endl;
    cout << "2. Exit" << endl;
    cout << "Enter choice: ";
}

void customerMenu(Customer* customer, BankClock* clock) {
    int choice = 0;
    while (true) {
        cout << "\n--- Customer Menu ---" << endl;
        cout << "1. View Accounts" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Transfer" << endl;
        cout << "5. View Transaction History" << endl;
        cout << "6. Process Monthly Update" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); choice = 0; }
        if (choice == 1) {
            customer->viewAccounts();
        } else if (choice == 2) {
            int accNo; double amt;
            cout << "Account Number: "; cin >> accNo;
            cout << "Amount: "; cin >> amt;
            customer->deposit(accNo, amt);
        } else if (choice == 3) {
            int accNo; double amt;
            cout << "Account Number: "; cin >> accNo;
            cout << "Amount: "; cin >> amt;
            customer->withdraw(accNo, amt);
        } else if (choice == 4) {
            int fromAcc, toAcc; double amt;
            cout << "From Account: "; cin >> fromAcc;
            cout << "To Account: "; cin >> toAcc;
            cout << "Amount: "; cin >> amt;
            customer->transfer(fromAcc, toAcc, amt);
        } else if (choice == 5) {
            int accNo;
            cout << "Account Number to view history: "; cin >> accNo;
            Account* acc = customer->getAccount(accNo);
            if (acc) acc->printTransactionHistory();
            else cout << "Account not found!" << endl;
        } else if (choice == 6) {
            cout << "Processing monthly update..." << endl;
            for (int i = 0; i < customer->getAccountCount(); ++i) {
                Account* acc = customer->getAccount(i);
                if (acc) {
                    acc->applyMonthlyUpdate();
                    cout << "Monthly update applied to account " << acc->getAccountNumber() << ". New balance: $" << acc->getBalance() << endl;
                }
            }
        } else if (choice == 7) {
            cout << "Logging out..." << endl;
            break;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
}

void adminMenu(Admin* admin, Customer* customers[], int* customerCount, BankClock* clock) {
    int choice = 0;
    while (true) {
        cout << "\n--- Admin Menu ---" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Delete Account" << endl;
        cout << "3. View All Customers" << endl;
        cout << "4. Process New Month" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); choice = 0; }
        if (choice == 1) {
            // Admin creates new account for a customer
            char uname[50];
            cout << "Customer username: "; cin >> uname;
            Customer* cust = 0;
            for (int i = 0; i < *customerCount; ++i) {
                if (strcmp(customers[i]->getUsername(), uname) == 0) {
                    cust = customers[i]; break;
                }
            }
            if (!cust) { cout << "Customer not found!" << endl; continue; }
            if (cust->getAccountCount() >= 5) { cout << "Max 5 accounts per customer!" << endl; continue; }
            char type[20], name[100]; int accNo; double amt;
            cout << "Account type (savings/current/loan): "; cin >> type;
            cout << "Account holder name: "; cin >> name;
            cout << "Account number: "; cin >> accNo;
            // Check for unique account number across all customers
            bool accExists = false;
            for (int i = 0; i < *customerCount; ++i) {
                Customer* c = customers[i];
                for (int j = 0; j < c->getAccountCount(); ++j) {
                    Account* a = c->getAccount(j);
                    if (a && a->getAccountNumber() == accNo) { accExists = true; break; }
                }
                if (accExists) break;
            }
            if (accExists) { cout << "Account number already exists! Please choose a unique account number." << endl; continue; }
            cout << "Initial amount: "; cin >> amt;
            Account* acc = AccountFactory::createAccount(type, name, accNo, amt);
            if (!acc) { cout << "Invalid account type!" << endl; continue; }
            cust->addAccount(acc);
            clock->registerObserver(acc);
            cout << "Account created and registered for monthly updates." << endl;
        } else if (choice == 2) {
            char uname[50]; int accNo;
            cout << "Customer username: "; cin >> uname;
            cout << "Account number: "; cin >> accNo;
            Customer* cust = 0;
            for (int i = 0; i < *customerCount; ++i) {
                if (strcmp(customers[i]->getUsername(), uname) == 0) {
                    cust = customers[i]; break;
                }
            }
            if (!cust) { cout << "Customer not found!" << endl; continue; }
            cust->removeAccount(accNo);
            cout << "Account deleted." << endl;
        } else if (choice == 3) {
            cout << "\n--- All Customers and Accounts ---" << endl;
            if (*customerCount == 0) {
                cout << "No customers found." << endl;
            } else {
                admin->viewAllCustomers(customers, *customerCount);
            }
        } else if (choice == 4) {
            cout << "Processing new month for all accounts..." << endl;
            clock->notifyAll();
            for (int i = 0; i < *customerCount; ++i) {
                Customer* cust = customers[i];
                for (int j = 0; j < cust->getAccountCount(); ++j) {
                    Account* acc = cust->getAccount(j);
                    if (acc) {
                        cout << "Monthly update applied to account " << acc->getAccountNumber() << ". New balance: $" << acc->getBalance() << endl;
                    }
                }
            }
        } else if (choice == 5) {
            cout << "Logging out..." << endl;
            break;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
} 