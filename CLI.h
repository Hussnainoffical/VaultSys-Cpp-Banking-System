#ifndef CLI_H
#define CLI_H

#include "Customer.h"
#include "Admin.h"
#include "BankClock.h"

void showMainMenu();
void customerMenu(Customer* customer, BankClock* clock);
void adminMenu(Admin* admin, Customer* customers[], int* customerCount, BankClock* clock);

#endif // CLI_H 