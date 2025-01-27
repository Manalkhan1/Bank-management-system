
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
