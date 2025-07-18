#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "LoanAccount.h"
#include "Customer.h"
#include "Admin.h"
#include "AccountFactory.h"
#include "BankClock.h"
#include "CLI.h"
#include "UserCredentials.h"
#include "DataIO.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    Customer* customers[100];
    int customerCount = 0;
    Admin* admins[10];
    int adminCount = 0;
    UserCredentials users[110];
    int userCount = loadUsers("users.txt", users, 110);
    BankClock clock;
    loadAccounts("accounts.txt", customers, &customerCount, 100);
    loadTransactions("transactions.txt", customers, customerCount);

    while (true) {
        showMainMenu();
        cout << "3. Register" << endl;
        int mainChoice;
        cin >> mainChoice;
        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); mainChoice = 0; }
        if (mainChoice == 1) {
            char username[50], password[50], role[20];
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;
            bool found = false;
            for (int i = 0; i < userCount; ++i) {
                if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
                    // Trim trailing spaces from role
                    int len = strlen(users[i].role);
                    while (len > 0 && (users[i].role[len-1] == ' ' || users[i].role[len-1] == '\r' || users[i].role[len-1] == '\n')) users[i].role[--len] = '\0';
                    strcpy(role, users[i].role); found = true; break;
                }
            }
            if (!found) {
                cout << "Login failed!" << endl;
                continue;
            }
            if (strcmp(role, "admin") == 0) {
                Admin* admin = new Admin(username, password);
                admins[adminCount++] = admin;
                adminMenu(admin, customers, &customerCount, &clock);
            } else if (strcmp(role, "customer") == 0) {
                Customer* customer = 0;
                for (int i = 0; i < customerCount; ++i) {
                    if (strcmp(customers[i]->getUsername(), username) == 0) {
                        customer = customers[i];
                        break;
                    }
                }
                if (!customer) {
                    customer = new Customer(username, password);
                    customers[customerCount++] = customer;
                }
                customerMenu(customer, &clock);
            } else {
                cout << "Unknown role!" << endl;
            }
        } else if (mainChoice == 2) {
            cout << "Saving data and exiting BankPro. Goodbye!" << endl;
            saveUsers("users.txt", users, userCount);
            saveAccounts("accounts.txt", customers, customerCount);
            saveTransactions("transactions.txt", customers, customerCount);
            break;
        } else if (mainChoice == 3) {
            if (userCount >= 110) { cout << "User limit reached!" << endl; continue; }
            char username[50], password[50];
            cout << "Choose username: "; cin >> username;
            cout << "Choose password: "; cin >> password;
            // Check for duplicate username
            bool exists = false;
            for (int i = 0; i < userCount; ++i) {
                if (strcmp(users[i].username, username) == 0) { exists = true; break; }
            }
            if (exists) { cout << "Username already exists!" << endl; continue; }
            strncpy(users[userCount].username, username, 49); users[userCount].username[49] = '\0';
            strncpy(users[userCount].password, password, 49); users[userCount].password[49] = '\0';
            strncpy(users[userCount].role, "customer", 19); users[userCount].role[19] = '\0';
            userCount++;
            // Append to users.txt
            ofstream fout("users.txt", ios::app);
            if (fout) { fout << username << ',' << password << ",customer" << endl; fout.close(); }
            cout << "Registration successful! You can now log in as a customer." << endl;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
    return 0;
} 