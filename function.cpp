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
       
