   #include<iostream
   #include <fstream>
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

