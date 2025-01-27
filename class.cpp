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
  
