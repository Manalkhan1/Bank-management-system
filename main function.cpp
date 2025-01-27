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
