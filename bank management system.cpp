#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <stdexcept>

using namespace std;

struct Account {
    int accountNumber;
    char name[50];
    double balance;
    char pin[10];
};

struct Recipient {
    int accountNumber;
    char name[50];
};

Recipient recipients[100];
int recipientCount = 0;

void saveAccountsToFile(Account accounts[], int count) {
    try {
        ofstream outFile("accounts.txt");
        if (!outFile) {
            throw runtime_error("Error opening file for writing.");
        }
        for (int i = 0; i < count; i++) {
            outFile << accounts[i].accountNumber << " "
                    << accounts[i].name << " "
                    << accounts[i].balance << " "
                    << accounts[i].pin << endl;
        }
        outFile.close();
    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
}

int loadAccountsFromFile(Account accounts[], int maxSize) {
    try {
        ifstream inFile("accounts.txt");
        if (!inFile) {
            throw runtime_error("Error opening file for reading.");
        }
        int count = 0;
        while (count < maxSize && inFile >> accounts[count].accountNumber >> accounts[count].name >> accounts[count].balance >> accounts[count].pin) {
            count++;
        }
        inFile.close();
        return count;
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 0;
    }
}

bool authenticatePin(Account accounts[], int index) {
    char pin[10];
    cout << "Enter PIN for account number " << accounts[index].accountNumber << ": ";
    cin >> pin;
    if (strcmp(accounts[index].pin, pin) != 0) {
        cout << "Error: Incorrect PIN." << endl;
        return false;
    }
    return true;
}

bool login(Account accounts[], int count, int &loggedInIndex) {
    int accountNumber;
    char pin[10];

    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter PIN: ";
    cin >> pin;

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accountNumber && strcmp(accounts[i].pin, pin) == 0) {
            loggedInIndex = i;
            cout << "Login successful! Welcome, " << accounts[i].name << ".\n";
            return true;
        }
    }

    cout << "Error: Invalid account number or PIN." << endl;
    return false;
}

void addAccount(Account accounts[], int &count, int maxSize) {
    if (count >= maxSize) {
        cout << "Error: Maximum account limit reached." << endl;
        return;
    }

    Account newAccount;
    cout << "Enter account number: ";
    cin >> newAccount.accountNumber;
    cout << "Enter name: ";
    cin.ignore();
    cin.getline(newAccount.name, 50);
    cout << "Enter initial deposit: ";
    cin >> newAccount.balance;
    if (newAccount.balance < 0) {
        cout << "Error: Initial deposit cannot be negative." << endl;
        return;
    }
    cout << "Enter PIN: ";
    cin >> newAccount.pin;

    accounts[count] = newAccount;
    count++;
    cout << "Account added successfully!" << endl;
}

void displayAccounts(Account accounts[], int count) {
    if (count == 0) {
        cout << "No accounts to display." << endl;
        return;
    }

    cout << left << setw(15) << "Account No." << setw(20) << "Name" << setw(15) << "Balance" << endl;
    cout << string(50, '-') << endl;
    for (int i = 0; i < count; i++) {
        cout << left << setw(15) << accounts[i].accountNumber
             << setw(20) << accounts[i].name
             << setw(15) << accounts[i].balance << endl;
    }
}

void addRecipient(int accountNumber, const char name[]) {
    recipients[recipientCount].accountNumber = accountNumber;
    strcpy(recipients[recipientCount].name, name);
    recipientCount++;
    cout << "Recipient added successfully!\n";
}

void displayRecipients() {
    if (recipientCount == 0) {
        cout << "No recipients to display." << endl;
        return;
    }

    cout << left << setw(15) << "Account No." << setw(20) << "Name" << endl;
    cout << string(35, '-') << endl;
    for (int i = 0; i < recipientCount; i++) {
        cout << left << setw(15) << recipients[i].accountNumber
             << setw(20) << recipients[i].name << endl;
    }
}

void deposit(Account accounts[], int count) {
    int accountNumber;
    double amount;

    cout << "Enter account number: ";
    cin >> accountNumber;

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            if (authenticatePin(accounts, i)) {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                if (amount <= 0) {
                    cout << "Error: Deposit amount must be greater than zero." << endl;
                    return;
                }
                accounts[i].balance += amount;
                cout << "Deposit successful! New balance: " << accounts[i].balance << endl;
            }
            return;
        }
    }
    cout << "Error: Account not found." << endl;
}

void withdraw(Account accounts[], int count) {
    int accountNumber;
    double amount;

    cout << "Enter account number: ";
    cin >> accountNumber;

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            if (authenticatePin(accounts, i)) {
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                if (amount <= 0) {
                    cout << "Error: Withdrawal amount must be greater than zero." << endl;
                    return;
                }
                if (accounts[i].balance < amount) {
                    cout << "Error: Insufficient balance." << endl;
                    return;
                }
                accounts[i].balance -= amount;
                cout << "Withdrawal successful! New balance: " << accounts[i].balance << endl;
            }
            return;
        }
    }
    cout << "Error: Account not found." << endl;
}

void onlinePayment(Account accounts[], int count) {
    int senderAccount, recipientAccount;
    double amount;

    cout << "Enter your account number: ";
    cin >> senderAccount;

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == senderAccount) {
            if (authenticatePin(accounts, i)) {
                cout << "Enter recipient account number: ";
                cin >> recipientAccount;
                cout << "Enter amount to transfer: ";
                cin >> amount;

                if (amount <= 0) {
                    cout << "Error: Transfer amount must be greater than zero." << endl;
                    return;
                }
                if (accounts[i].balance < amount) {
                    cout << "Error: Insufficient balance." << endl;
                    return;
                }
                for (int j = 0; j < count; j++) {
                    if (accounts[j].accountNumber == recipientAccount) {
                        accounts[i].balance -= amount;
                        accounts[j].balance += amount;
                        addRecipient(recipientAccount, accounts[j].name);
                        cout << "Transfer successful! New balance: " << accounts[i].balance << endl;
                        return;
                    }
                }
                cout << "Transfer successful! New balance: " << accounts[i].balance << endl;
            }
            return;
        }
    }
    cout << "Error: Account not found." << endl;
}

int main() {
    const int MAX_ACCOUNTS = 100;
    Account accounts[MAX_ACCOUNTS];
    int accountCount = loadAccountsFromFile(accounts, MAX_ACCOUNTS);

    int choice;
    do {
        cout << "\n--- Welcome to Bank Management System ---\n";
        cout << "1. Login\n2. Create Accounts\n3. Display Accounts\n4. Add Recipient\n5. Display Recipients \n6. Deposit Money \n7. Withdraw Money\ \n8. Make Online Payment\n9. Exit\nEnter your choice: ";
        cin >> choice;

        try {
            switch (choice) {
            	case 1: {
                    int loggedInIndex;
                    if (login(accounts, accountCount, loggedInIndex)) {
                        cout << "You are now logged in!\n";
                    }
                    break;
                case 2:
                    addAccount(accounts, accountCount, MAX_ACCOUNTS);
                    break;
                case 3:
                    displayAccounts(accounts, accountCount);
                    break;
                case 4: {
                    int recipientAccount;
                    char recipientName[50];
                    cout << "Enter recipient account number: ";
                    cin >> recipientAccount;
                    cout << "Enter recipient name: ";
                    cin.ignore();
                    cin.getline(recipientName, 50);
                    addRecipient(recipientAccount, recipientName);
                    break;
                }
                case 5:
                    displayRecipients();
                    break;
                case 6:
                    deposit(accounts, accountCount);
                    break;
                case 7:
                    withdraw(accounts, accountCount);
                    break;
                case 8:
                    onlinePayment(accounts, accountCount);
                    break;
                }
                case 9:
                    saveAccountsToFile(accounts, accountCount);
                    cout << "Goodbye!" << endl;
                    break;
                default:
                    throw invalid_argument("Invalid choice. Please try again.");
            }
        } catch (const exception &e) {
            cout << e.what() << endl;
        }
    } while (choice != 9);

    return 0;
}   
