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
