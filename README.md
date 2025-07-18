#  VaultSys — Secure Virtual Banking System in Classic C++

**VaultSys** is a high-integrity, role-based virtual banking system built in. It showcases mastery of **OOP**, **SOLID design principles**, and **real-world design patterns** — all implemented with raw pointers, arrays, and manual memory/file management.

---



##  Project Highlights

-  **Role-Based CLI System** – Admin & Customer menus with full banking functionality
-  **Design Patterns** – Uses **Factory** for account creation and **Observer** for monthly updates
-  **Full Data Persistence** – Loads/saves users, accounts, and transactions from `.txt` files
-  
-  **Secure & Validated** – Input validation, access control, and defensive programming throughout

---

##  How the Project Works

### 1.  User Roles

####  Admin:
- Create/Delete accounts for customers
- View all customer data
- Process monthly interest updates for all accounts

####  Customer:
- Register/login with a secure username/password
- Manage accounts: deposit, withdraw, transfer
- View transaction history
- Process monthly updates for their own accounts

---

### 2. Data Storage Files

| File             | Description                                        | Format Example |
|------------------|----------------------------------------------------|----------------|
| `users.txt`      | Stores login credentials and roles                 | `john123,pass123,customer` |
| `accounts.txt`   | Stores customer accounts                           | `10001,Savings,John Doe,5000` |
| `transactions.txt` | Logs all account transactions                    | `10001,2025-07-15,Deposit,500,-,-` |

---

### 3.  Main Features & Usage Guide

####  A. Registration
- Only **customers** can register via CLI.
- Unique username and password.
- Saved in `users.txt`.

####  B. Login
- Username/password validated against `users.txt`.
- Role determines menu (admin/customer).

####  C. Customer Menu
- **View Accounts** – See all your accounts (balance, type)
- **Deposit/Withdraw** – Manage money securely
- **Transfer** – Move funds between your own accounts
- **View Transaction History** – Track all account activity
- **Monthly Update** – Apply interest to Savings/Loan accounts
- **Logout** – Return to main menu

####  D. Admin Menu
- **Create New Account** – For existing customers
- **Delete Account** – Remove customer accounts
- **View All Customers** – List all users and their accounts
- **Process New Month** – Apply monthly interest to ALL accounts
- **Logout** – Return to main menu

---

### 4.  Constraints & Error Handling

- **Unique Usernames & Account Numbers**
- **Input Validation** – No negative deposits, invalid types, etc.
- **Role Enforcement** – Admins only access admin features
- **Access Control** – Customers can only access their own data
- **File Integrity Checks** – Skips malformed/empty lines

---

### 5.  Data Persistence & Lifecycle

| Event               | Behavior                             |
|---------------------|--------------------------------------|
| **Program Start**   | Loads users, accounts, transactions  |
| **Program Exit**    | Saves all data back to `.txt` files  |
| **Transactions**    | Logged and saved after every action  |
| **Monthly Updates** | Logged as “Interest” transactions    |



