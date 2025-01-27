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
