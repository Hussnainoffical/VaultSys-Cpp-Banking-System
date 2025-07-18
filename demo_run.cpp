#include "Customer.h"
#include "AccountFactory.h"
#include "BankClock.h"
#include "DataIO.h"
#include <iostream>
using namespace std;

int main() {
    cout << "Running BankPro Demo...\n";

    // Create a customer and a couple of accounts
    Customer demoCustomer("john", "123");
    Account* acc1 = AccountFactory::createAccount("savings", "John", 1001, 0.0);
    Account* acc2 = AccountFactory::createAccount("current", "John", 1002, 0.0);

    demoCustomer.addAccount(acc1);
    demoCustomer.addAccount(acc2);

    acc1->deposit(1000);
    acc2->deposit(2000);
    acc1->withdraw(200);
    demoCustomer.transfer(1001, 1002, 300);

    BankClock clock;
    clock.registerObserver(acc1);
    clock.registerObserver(acc2);
    clock.notifyAll(); // Apply monthly interest

    cout << "\n--- Transaction History for Savings Account ---\n";
    acc1->printTransactionHistory();
    cout << "\n--- Transaction History for Current Account ---\n";
    acc2->printTransactionHistory();

    // Save data
    Customer* customers[1] = { &demoCustomer };
    saveAccounts("accounts.txt", customers, 1);
    saveTransactions("transactions.txt", customers, 1);

    cout << "Demo complete. Data saved to accounts.txt and transactions.txt\n";
    return 0;
} 