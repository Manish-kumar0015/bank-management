#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
using namespace std;

//------------------------------
// Payment Record Structure
//------------------------------
struct PaymentRecord {
    int accountNumber;
    double amount;
    string description;
};

//------------------------------
// Account Class
//------------------------------
class Account {
private:
    int accountNumber;
    string name;
    double balance;
public:
    Account(int accNumber, const string &accName, double initialBalance)
        : accountNumber(accNumber), name(accName), balance(initialBalance) {}

    int getAccountNumber() const { return accountNumber; }
    string getName() const { return name; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            return false;
        }
        balance -= amount;
        return true;
    }

    void display() const {
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Name: " << name << "\n";
        cout << "Balance: " << balance << "\n";
    }

    void setName(const string &newName) {
        name = newName;
    }
};

//------------------------------
// Bank Management System Class
//------------------------------
class BankManagementSystem {
private:
    vector<Account> accounts;
    vector<PaymentRecord> paymentRecords;
    int nextAccountNumber;

public:
    BankManagementSystem();

    // File Handling
    void saveAccounts();
    void loadAccounts();
    void savePayments();
    void loadPayments();

    Account* findAccount(int accNumber);
    void addNewUser();
    void deposit();
    void withdraw();
    void transfer();
    void payment();
    void searchUserRecord();
    void editUserRecord();
    void deleteUserRecord();
    void showAllRecords();
    void showPaymentRecords();
};

// Definitions of BankManagementSystem member functions
BankManagementSystem::BankManagementSystem()
{
    nextAccountNumber = 1001;

    loadAccounts();
    loadPayments();
}
Account* BankManagementSystem::findAccount(int accNumber) {
    for (auto &acc : accounts) {
        if (acc.getAccountNumber() == accNumber)
            return &acc;
    }
    return nullptr;
}

void BankManagementSystem::addNewUser() {
    string name;
    double initialDeposit;
    cout << "Enter user name: ";
    getline(cin, name);
    cout << "Enter initial deposit amount: ";
    cin >> initialDeposit;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Account newAccount(nextAccountNumber++, name, initialDeposit);
    accounts.push_back(newAccount);
    saveAccounts(); 
    cout << "Account created successfully! Your account number is: "
        << newAccount.getAccountNumber() << "\n";
}

void BankManagementSystem::deposit() {
    int accNumber;
    double amount;
    cout << "Enter account number: ";
    cin >> accNumber;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Account* acc = findAccount(accNumber);
    if (!acc) {
        cout << "Account not found!\n";
        return;
    }
    cout << "Enter deposit amount: ";
    cin >> amount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    acc->deposit(amount);
    saveAccounts(); 
    cout << "Deposit successful. New Balance: " << acc->getBalance() << "\n";
}

void BankManagementSystem::withdraw() {
    int accNumber;
    double amount;
    cout << "Enter account number: ";
    cin >> accNumber;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Account* acc = findAccount(accNumber);
    if (!acc) {
        cout << "Account not found!\n";
        return;
    }
    cout << "Enter withdrawal amount: ";
    cin >> amount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (acc->withdraw(amount)) {
        saveAccounts(); 
        cout << "Withdrawal successful. New Balance: " << acc->getBalance() << "\n";
    } else {
        cout << "Insufficient balance!\n";
    }
}

void BankManagementSystem::transfer() {
    int sourceAcc, targetAcc;
    double amount;
    cout << "Enter source account number: ";
    cin >> sourceAcc;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Account* src = findAccount(sourceAcc);
    if (!src) {
        cout << "Source account not found!\n";
        return;
    }

    cout << "Enter target account number: ";
    cin >> targetAcc;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Account* tgt = findAccount(targetAcc);
    if (!tgt) {
        cout << "Target account not found!\n";
        return;
    }

    cout << "Enter transfer amount: ";
    cin >> amount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (src->withdraw(amount)) {
        tgt->deposit(amount);
        saveAccounts(); 
        cout << "Transfer successful.\n";
    } else {
        cout << "Insufficient balance in source account!\n";
    }
}

void BankManagementSystem::payment() {
    int accNumber;
    double amount;
    string description;
    cout << "Enter account number: ";
    cin >> accNumber;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Account* acc = findAccount(accNumber);
    if (!acc) {
        cout << "Account not found!\n";
        return;
    }
    cout << "Enter payment amount: ";
    cin >> amount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter payment description: ";
    getline(cin, description);

    if (acc->withdraw(amount)) {
        PaymentRecord pr { accNumber, amount, description };
        paymentRecords.push_back(pr);
        saveAccounts(); 
        savePayments();   
        cout << "Payment successful. New Balance: " << acc->getBalance() << "\n";
    } else {
        cout << "Insufficient balance for payment!\n";
    }
}

void BankManagementSystem::searchUserRecord() {
    int accNumber;
    cout << "Enter account number to search: ";
    cin >> accNumber;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Account* acc = findAccount(accNumber);
    if (!acc) {
        cout << "Account not found!\n";
    } else {
        acc->display();
    }
}

void BankManagementSystem::editUserRecord() {
    int accNumber;
    cout << "Enter account number to edit: ";
    cin >> accNumber;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Account* acc = findAccount(accNumber);
    if (!acc) {
        cout << "Account not found!\n";
    } else {
        string newName;
        cout << "Enter new name: ";
        getline(cin, newName);
        acc->setName(newName);
        saveAccounts(); 
        cout << "Account updated successfully.\n";
    }
}

void BankManagementSystem::deleteUserRecord() {
    int accNumber;
    cout << "Enter account number to delete: ";
    cin >> accNumber;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found = false;
    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if (it->getAccountNumber() == accNumber) {
            accounts.erase(it);
            saveAccounts(); 
            cout << "Account deleted successfully.\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Account not found!\n";
    }
}

void BankManagementSystem::showAllRecords() {
    if (accounts.empty()) {
        cout << "No accounts available.\n";
        return;
    }
    for (auto &acc : accounts) {
        acc.display();
        cout << "-------------------------\n";
    }
}

void BankManagementSystem::showPaymentRecords() {
    if (paymentRecords.empty()) {
        cout << "No payment records available.\n";
        return;
    }
    for (auto &pr : paymentRecords) {
        cout << "Account Number: " << pr.accountNumber << "\n";
        cout << "Payment Amount: " << pr.amount << "\n";
        cout << "Description: " << pr.description << "\n";
        cout << "-------------------------\n";
    }
}

//------------------------------
// ATM System Class
//------------------------------
class ATMSystem {
private:
    BankManagementSystem* bank; // pointer to BankManagementSystem
    int currentAccountNumber;   // -1 if not logged in

public:
    ATMSystem(BankManagementSystem* b) : bank(b), currentAccountNumber(-1) {}

    void userLogin() {
        int accNumber;
        cout << "Enter your account number: ";
        cin >> accNumber;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Account* acc = bank->findAccount(accNumber);
        if (acc) {
            currentAccountNumber = accNumber;
            cout << "Login successful! Welcome, " << acc->getName() << "\n";
        } else {
            cout << "Account not found! Please try again.\n";
        }
    }

    void checkBalance() {
        if (currentAccountNumber == -1) {
            cout << "Please login first.\n";
            return;
        }
        Account* acc = bank->findAccount(currentAccountNumber);
        if (acc) {
            cout << "Your current balance is: " << acc->getBalance() << "\n";
        }
    }

    void withdrawAmount() {
        if (currentAccountNumber == -1) {
            cout << "Please login first.\n";
            return;
        }
        double amount;
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Account* acc = bank->findAccount(currentAccountNumber);
        if (acc) {
            if (acc->withdraw(amount)) {
                bank->saveAccounts();
                cout << "Withdrawal successful. New balance: " << acc->getBalance() << "\n";
            } else {
                cout << "Insufficient balance.\n";
            }
        }
    }

    void accountDetails() {
        if (currentAccountNumber == -1) {
            cout << "Please login first.\n";
            return;
        }
        Account* acc = bank->findAccount(currentAccountNumber);
        if (acc) {
            acc->display();
        }
    }

    void atmMenu() {
        int choice;
        do {
            cout << "\n--- ATM System Menu ---\n";
            cout << "1. User Login\n";
            cout << "2. Check Balance\n";
            cout << "3. Withdraw Amount\n";
            cout << "4. Account Details\n";
            cout << "5. Logout\n";
            cout << "6. Go Back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
                case 1: userLogin(); break;
                case 2: checkBalance(); break;
                case 3: withdrawAmount(); break;
                case 4: accountDetails(); break;
                case 5:
                    currentAccountNumber = -1;
                    cout << "Logged out successfully.\n";
                    break;
                case 6:
                    cout << "Returning to Main Menu.\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 6);
    }
};

//------------------------------
// Bank Management Menu Function
//------------------------------
void bankManagementMenu(BankManagementSystem &bank) {
    int choice;
    do {
        cout << "\n--- Bank Management System Menu ---\n";
        cout << "1. New User (Create Account)\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer\n";
        cout << "5. Payment\n";
        cout << "6. Search User Record\n";
        cout << "7. Edit User Record\n";
        cout << "8. Delete User Record\n";
        cout << "9. Show All Records\n";
        cout << "10. Show Payment Records\n";
        cout << "11. Go Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:  bank.addNewUser(); break;
            case 2:  bank.deposit(); break;
            case 3:  bank.withdraw(); break;
            case 4:  bank.transfer(); break;
            case 5:  bank.payment(); break;
            case 6:  bank.searchUserRecord(); break;
            case 7:  bank.editUserRecord(); break;
            case 8:  bank.deleteUserRecord(); break;
            case 9:  bank.showAllRecords(); break;
            case 10: bank.showPaymentRecords(); break;
            case 11:
                cout << "Returning to Main Menu.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 11);
}

void BankManagementSystem::saveAccounts()
{
    ofstream fout("accounts.txt");

    for(auto &acc : accounts)
    {
        fout
        << acc.getAccountNumber() << "|"
        << acc.getName() << "|"
        << acc.getBalance()
        << endl;
    }

    fout.close();
}

void BankManagementSystem::loadAccounts()
{
    ifstream fin("accounts.txt");

    if(!fin)
        return;

    string line;

    while(getline(fin,line))
    {
        stringstream ss(line);

        string acc,name,balance;

        getline(ss,acc,'|');
        getline(ss,name,'|');
        getline(ss,balance);

        Account a(
            stoi(acc),
            name,
            stod(balance)
        );

        accounts.push_back(a);

        nextAccountNumber =
            max(nextAccountNumber,
            stoi(acc)+1);
    }

    fin.close();
}

void BankManagementSystem::savePayments()
{
    ofstream fout("payments.txt");

    for (auto &p : paymentRecords)
    {
        fout << p.accountNumber << "|"
             << p.amount << "|"
             << p.description << endl;
    }

    fout.close();
}

void BankManagementSystem::loadPayments()
{
    ifstream fin("payments.txt");

    if (!fin)
        return;

    string line;

    while (getline(fin, line))
    {
        stringstream ss(line);

        PaymentRecord p;

        string acc, amount;

        getline(ss, acc, '|');
        getline(ss, amount, '|');
        getline(ss, p.description);

        p.accountNumber = stoi(acc);
        p.amount = stod(amount);

        paymentRecords.push_back(p);
    }

    fin.close();
}
//------------------------------
// Main Function
//------------------------------
int main() {
    BankManagementSystem bank;
    ATMSystem atm(&bank);

    int choice;
    do {
        cout << "\n=== Main Menu ===\n";
        cout << "1. ATM System\n";
        cout << "2. Bank Management System\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                atm.atmMenu();
                break;
            case 2:
                bankManagementMenu(bank);
                break;
            case 3:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}