#  VaultSys — Secure Virtual Banking System in Classic C++

**VaultSys** is a high-integrity, role-based virtual banking system built in **pure C++ (C++11)** without using STL or modern C++ abstractions. It showcases mastery of **OOP**, **SOLID design principles**, and **real-world design patterns** — all implemented with raw pointers, arrays, and manual memory/file management.

---

##  Key Features

-  **Role-Based Access:** Admin vs. Customer
-  **Account Types:** Savings, Current, Loan
-  **Banking Operations:** Deposit, Withdraw, Transfer
-  **Transaction Logging:** All actions logged and persisted
-  **Monthly Automation:** Interest application via Observer pattern
-  **Design Patterns:** Factory (account creation), Observer (monthly update)
-  **Data Persistence:** Users, accounts, and transactions saved/loaded via file I/O
-  **No STL:** No `vector`, `map`, `auto`, or smart pointers used

---

##  Project Structure

VaultSys/
├── src/
│ ├── Account., SavingsAccount., CurrentAccount., LoanAccount.
│ ├── User., Customer., Admin., UserCredentials.
│ ├── Transaction., BankClock., AccountFactory.*
│ ├── CLI., DataIO., DateUtil.*
│ └── main.cpp
├── test/
│ └── demo_run.cpp
├── data/
│ ├── users.txt
│ ├── accounts.txt
│ ├── transactions.txt
