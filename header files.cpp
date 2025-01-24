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
