#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    string name;
    string accountType;
    double balance;

public:
    // Create a new account
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        cin.ignore();

        cout << "Enter Account Holder Name: ";
        getline(cin, name);

        cout << "Enter Account Type (Saving/Current): ";
        getline(cin, accountType);

        cout << "Enter Initial Deposit: ";
        cin >> balance;

        cout << "\nAccount created successfully!\n";
    }

    // Display account details
    void showAccount() const {
        cout << "\n-----------------------------";
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nAccount Holder : " << name;
        cout << "\nAccount Type   : " << accountType;
        cout << "\nBalance        : Rs. " << fixed << setprecision(2)
             << balance;
        cout << "\n-----------------------------\n";
    }

    // Deposit money
    void deposit(double amount) {
        balance += amount;
        cout << "\nRs. " << amount << " deposited successfully.\n";
        cout << "New Balance: Rs. " << balance << endl;
    }

    // Withdraw money
    void withdraw(double amount) {
        if (amount > balance) {
            cout << "\nInsufficient balance!\n";
        } else {
            balance -= amount;
            cout << "\nRs. " << amount << " withdrawn successfully.\n";
            cout << "Remaining Balance: Rs. " << balance << endl;
        }
    }

    // Return account number
    int getAccountNumber() const {
        return accountNumber;
    }

    // Save account to file
    void saveToFile(ofstream &file) const {
        file << accountNumber << endl;
        file << name << endl;
        file << accountType << endl;
        file << balance << endl;
    }

    // Read account from file
    bool readFromFile(ifstream &file) {
        if (!(file >> accountNumber))
            return false;

        file.ignore();

        getline(file, name);
        getline(file, accountType);
        file >> balance;
        file.ignore();

        return true;
    }
};

// Create account
void createAccount() {
    BankAccount account;
    account.createAccount();

    ofstream file("accounts.txt", ios::app);

    if (!file) {
        cout << "\nError opening file!\n";
        return;
    }

    account.saveToFile(file);
    file.close();
}

// Display all accounts
void displayAllAccounts() {
    ifstream file("accounts.txt");

    if (!file) {
        cout << "\nNo accounts found.\n";
        return;
    }

    BankAccount account;
    bool found = false;

    cout << "\n========== ALL ACCOUNTS ==========\n";

    while (account.readFromFile(file)) {
        account.showAccount();
        found = true;
    }

    file.close();

    if (!found)
        cout << "\nNo accounts found.\n";
}

// Search account
void searchAccount() {
    int number;

    cout << "\nEnter Account Number: ";
    cin >> number;

    ifstream file("accounts.txt");

    if (!file) {
        cout << "\nNo accounts found.\n";
        return;
    }

    BankAccount account;
    bool found = false;

    while (account.readFromFile(file)) {
        if (account.getAccountNumber() == number) {
            cout << "\nAccount Found!\n";
            account.showAccount();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount not found.\n";
}

// Deposit money
void depositMoney() {
    int number;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> number;

    fstream file("accounts.txt", ios::in);

    if (!file) {
        cout << "\nNo accounts found.\n";
        return;
    }

    BankAccount account;
    bool found = false;

    while (account.readFromFile(file)) {
        if (account.getAccountNumber() == number) {
            found = true;

            cout << "Enter Amount to Deposit: ";
            cin >> amount;

            if (amount <= 0) {
                cout << "\nInvalid amount!\n";
            } else {
                account.deposit(amount);
            }

            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount not found.\n";
}

// Withdraw money
void withdrawMoney() {
    int number;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> number;

    ifstream file("accounts.txt");

    if (!file) {
        cout << "\nNo accounts found.\n";
        return;
    }

    BankAccount account;
    bool found = false;

    while (account.readFromFile(file)) {
        if (account.getAccountNumber() == number) {
            found = true;

            cout << "Enter Amount to Withdraw: ";
            cin >> amount;

            if (amount <= 0) {
                cout << "\nInvalid amount!\n";
            } else {
                account.withdraw(amount);
            }

            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount not found.\n";
}

// Main menu
int main() {
    int choice;

    do {
        cout << "\n\n====================================";
        cout << "\n       BANK MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Create New Account";
        cout << "\n2. Display All Accounts";
        cout << "\n3. Search Account";
        cout << "\n4. Deposit Money";
        cout << "\n5. Withdraw Money";
        cout << "\n6. Exit";
        cout << "\n====================================";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;

            case 2:
                displayAllAccounts();
                break;

            case 3:
                searchAccount();
                break;

            case 4:
                depositMoney();
                break;

            case 5:
                withdrawMoney();
                break;

            case 6:
                cout << "\nThank you for using Bank Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
