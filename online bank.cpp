#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

// Structure to represent a bank account
struct Account {
    int accountNumber;
    string name;
    double balance;
    string pin;
};

// Structure to store recipient details
struct Recipient {
    int accountNumber;
    string name;
};

class Bank {
private:
    vector<Account> accounts;
    vector<Recipient> recipients;  

    // Function to save accounts to a file
    void saveAccountsToFile() {
        ofstream outFile("accounts.txt");
        if (!outFile) {
            cerr << "Error opening file for writing.\n";
            return;
        }
        for (size_t i = 0; i < accounts.size(); i++) {
            outFile << accounts[i].accountNumber << " "
                    << accounts[i].name << " "
                    << accounts[i].balance << " "
                    << accounts[i].pin << "\n";
        }
        outFile.close();
    }

    // Function to load accounts from a file
    void loadAccountsFromFile() {
        ifstream inFile("accounts.txt");
        if (!inFile) {
            cerr << "Error opening file for reading.\n";
            return;
        }
        Account acc;
        while (inFile >> acc.accountNumber >> acc.name >> acc.balance >> acc.pin) {
            accounts.push_back(acc);
        }
        inFile.close();
    }

public:
    Bank() {
        loadAccountsFromFile();
    }

    ~Bank() {
        saveAccountsToFile();
    }
    // Add a new account
    void addAccount(int accountNumber, const string &name, double initialDeposit, const string &pin) {
        if (initialDeposit < 0) {
            cout << "Error: Initial deposit cannot be negative.\n";
            return;
        }
        Account newAccount = {accountNumber, name, initialDeposit, pin};
        accounts.push_back(newAccount);
        cout << "Account added successfully!\n";
    }

    // Add a recipient to the list
    void addRecipient(int accountNumber, const string &name) {
        Recipient newRecipient = {accountNumber, name};
        recipients.push_back(newRecipient);
        cout << "Recipient added successfully!\n";
    }

    // Display all recipients
    void displayRecipients() {
        if (recipients.empty()) {
            cout << "No recipient accounts available.\n";
            return;
        }
        cout << left << setw(15) << "Recipient No." << setw(20) << "Name" << endl;
        cout << string(35, '-') << endl;
        for (size_t i = 0; i < recipients.size(); i++) {
            cout << left << setw(15) << recipients[i].accountNumber << setw(20) << recipients[i].name << endl;
        }
    }

    // Display all accounts
    void displayAccounts() {
        if (accounts.empty()) {
            cout << "No accounts to display.\n";
            return;
        }
        cout << left << setw(15) << "Account No." << setw(20) << "Name" << setw(15) << "Balance" << endl;
        cout << string(50, '-') << endl;
        for (size_t i = 0; i < accounts.size(); i++) {
            cout << left << setw(15) << accounts[i].accountNumber
                 << setw(20) << accounts[i].name
                 << setw(15) << accounts[i].balance << endl;
        }
    }

    // Search user record by account number
    Account* searchAccount(int accountNumber) {
        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i].accountNumber == accountNumber) {
                return &accounts[i]; // Return pointer to the found account
            }
        }
        return NULL; // Return NULL if account not found
    }

    // Make an online payment (Withdraw money and transfer to another account)
    bool makeOnlinePayment(int accountNumber, double amount, int recipientAccountNumber) {
        Account* senderAccount = searchAccount(accountNumber);
        if (!senderAccount) {
            cout << "Error: Sender account not found.\n";
            return false;
        }

        bool recipientExists = false;
        for (size_t i = 0; i < recipients.size(); i++) {
            if (recipients[i].accountNumber == recipientAccountNumber) {
                recipientExists = true;
                break;
            }
        }
        if (!recipientExists) {
            cout << "Error: Recipient account not found in recipient list.\n";
            return false;
        }

        if (senderAccount->balance < amount) {
            cout << "Error: Insufficient balance.\n";
            return false;
        }

        senderAccount->balance -= amount;
        cout << "Online payment successful! New sender balance: " << senderAccount->balance << "\n";
        return true;
    }

    // Deposit money into an account
    void deposit(int accountNumber, double amount) {
        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i].accountNumber == accountNumber) {
                if (amount <= 0) {
                    cout << "Error: Deposit amount must be greater than zero.\n";
                    return;
                }
                accounts[i].balance += amount;
                cout << "Deposit successful! New balance: " << accounts[i].balance << "\n";
                return;
            }
        }
        cout << "Error: Account not found.\n";
    }

    // Withdraw money from an account (PIN required)
    bool withdraw(int accountNumber, double amount, const string &pin) {
        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i].accountNumber == accountNumber) {
                if (accounts[i].pin != pin) {
                    cout << "Error: Incorrect PIN.\n";
                    return false; // PIN does not match
                }
                if (amount <= 0) {
                    cout << "Error: Withdrawal amount must be greater than zero.\n";
                    return false;
                }
                if (accounts[i].balance < amount) {
                    cout << "Error: Insufficient balance.\n";
                    return false;
                }
                accounts[i].balance -= amount;
                cout << "Withdrawal successful! New balance: " << accounts[i].balance << "\n";
                return true;
            }
        }
        cout << "Error: Account not found.\n";
        return false;
    }

    // ATM Withdrawal (PIN required)
    bool atmWithdrawal(int accountNumber, double amount, const string &pin) {
        return withdraw(accountNumber, amount, pin);
    }
};

// Function to display the initial menu (Create Account first, then Login)
void displayInitialMenu() {
    cout << "\n--- Welcome to Bank Management System ---\n";
    cout << "1. Create Account\n";
    cout << "2. Login\n";
    cout << "Enter your choice: ";
}

// Function to display the main menu for Bank Management System
void displayBankMenu() {
    cout << "\n--- Bank Management System ---\n";
    cout << "1. New User (Create Account)\n";
    cout << "2. Display Accounts\n";
    cout << "3. Display Recipients\n";
    cout << "4. Add Recipient\n";
    cout << "5. Deposit Money\n";
    cout << "6. Withdraw Money\n";
    cout << "7. Make Online Payment\n";
    cout << "8. ATM Withdrawal\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}

// Function to login
bool login(int &loggedInAccount, Bank &bank) {
    int accountNumber;
    string pin;
    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter PIN: ";
    cin >> pin;

    Account* account = bank.searchAccount(accountNumber);
    if (account && account->pin == pin) {
        loggedInAccount = accountNumber;
        cout << "Login successful!\n";
        return true;
    } else {
        cout << "Invalid account number or PIN.\n";
        return false;
    }
}

// Main function to start the program
int main() {
    Bank bank;
    int choice;
    int loggedInAccount = -1;  // -1 means no account logged in

    while (true) {
        displayInitialMenu();
        cin >> choice;

        if (choice == 1) {
            int accountNumber;
            string name, pin;
            double initialDeposit;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter name: ";
            cin.ignore(); // To clear the newline from the input buffer
            getline(cin, name);
            cout << "Enter initial deposit: ";
            cin >> initialDeposit;
            cout << "Enter PIN: ";
            cin >> pin;
            bank.addAccount(accountNumber, name, initialDeposit, pin);
        } else if (choice == 2) {
            bool loginSuccess = login(loggedInAccount, bank);
            if (!loginSuccess) continue;
        } else {
            cout << "Invalid choice.\n";
            continue;
        }

        while (loggedInAccount != -1) {
            displayBankMenu();
            cin >> choice;

            switch (choice) {
                case 1: {
                    // New User (Create Account)
                    int accountNumber;
                    string name, pin;
                    double initialDeposit;
                    cout << "Enter account number: ";
                    cin >> accountNumber;
                    cout << "Enter name: ";
                    cin.ignore(); // To clear the newline from the input buffer
                    getline(cin, name);
                    cout << "Enter initial deposit: ";
                    cin >> initialDeposit;
                    cout << "Enter PIN: ";
                    cin >> pin;
                    bank.addAccount(accountNumber, name, initialDeposit, pin);
                    break;
                }
                case 2:
                    // Display all accounts
                    bank.displayAccounts();
                    break;
                case 3:
                    // Display all recipients
                    bank.displayRecipients();
                    break;
                case 4: {
                    // Add a recipient
                    int recipientNumber;
                    string recipientName;
                    cout << "Enter recipient account number: ";
                    cin >> recipientNumber;
                    cout << "Enter recipient name: ";
                    cin.ignore(); // To clear the newline from the input buffer
                    getline(cin, recipientName);
                    bank.addRecipient(recipientNumber, recipientName);
                    break;
                }
                case 5: {
                    // Deposit Money
                    int accountNumber;
                    double amount;
                    cout << "Enter account number: ";
                    cin >> accountNumber;
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    bank.deposit(accountNumber, amount);
                    break;
                }
                case 6: {
                    // Withdraw Money
                    int accountNumber;
                    double amount;
                    string pin;
                    cout << "Enter account number: ";
                    cin >> accountNumber;
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    cout << "Enter PIN: ";
                    cin >> pin;
                    bank.withdraw(accountNumber, amount, pin);
                    break;
                }
                case 7: {
                    // Make Online Payment
                    int recipientNumber;
                    double amount;
                    cout << "Enter recipient account number: ";
                    cin >> recipientNumber;
                    cout << "Enter amount to pay: ";
                    cin >> amount;
                    bank.makeOnlinePayment(loggedInAccount, amount, recipientNumber);
                    break;
                }
                case 8: {
                    // ATM Withdrawal
                    int accountNumber;
                    double amount;
                    string pin;
                    cout << "Enter account number: ";
                    cin >> accountNumber;
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    cout << "Enter PIN: ";
                    cin >> pin;
                    bank.atmWithdrawal(accountNumber, amount, pin);
                    break;
                }
                case 9:
                    // Exit
                    loggedInAccount = -1;
                    cout << "Logged out successfully. Goodbye!\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        }
    }
}

