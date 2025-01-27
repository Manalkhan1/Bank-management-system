
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
