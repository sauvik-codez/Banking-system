#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>  // For system("cls") and system("clear") for cross-platform compatibility

using namespace std;

class Account {
private:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    Account() : balance(0.0) {}

    void createAccount() {
        cout << "Enter account number: ";
        cin >> accountNumber;
        cin.ignore();  // Ignore newline left in the buffer
        cout << "Enter account holder's name: ";
        getline(cin, accountHolderName);
        balance = 0.0;
        cout << "Account created successfully!" << endl;
    }

    void deposit() {
        double amount;
        cout << "Enter amount to deposit: ";
        cin >> amount;
        if (amount > 0) {
            balance += amount;
            cout << "Amount deposited successfully. New balance: " << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw() {
        double amount;
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Amount withdrawn successfully. New balance: " << balance << endl;
        } else if (amount > balance) {
            cout << "Insufficient funds." << endl;
        } else {
            cout << "Invalid withdrawal amount." << endl;
        }
    }

    void checkBalance() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder's Name: " << accountHolderName << endl;
        cout << "Current Balance: " << balance << endl;
    }

    void saveToFile() const {
        ofstream outFile("account.txt");
        outFile << accountNumber << endl;
        outFile << accountHolderName << endl;
        outFile << balance << endl;
        outFile.close();
    }

    void loadFromFile() {
        ifstream inFile("account.txt");
        if (inFile.is_open()) {
            getline(inFile, accountNumber);
            getline(inFile, accountHolderName);
            inFile >> balance;
            inFile.close();
        }
    }

    void deleteAccount() {
        // Delete account file
        if (remove("account.txt") == 0) {
            cout << "Account deleted successfully." << endl;
            accountNumber = "";
            accountHolderName = "";
            balance = 0.0;
        } else {
            cout << "Error deleting account." << endl;
        }
    }
};

void clearScreen() {
    // System-specific screen clearing
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    Account account;
    account.loadFromFile();

    int choice;
    do {
        clearScreen();
        cout << "Banking System Menu:\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Check Balance\n";
        cout << "5. Delete Account\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                account.createAccount();
                break;
            case 2:
                account.deposit();
                break;
            case 3:
                account.withdraw();
                break;
            case 4:
                account.checkBalance();
                break;
            case 5:
                account.deleteAccount();
                break;
            case 6:
                account.saveToFile();
                cout << "Exiting the application. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
        if (choice != 6) {
            cin.ignore(); // Ignore newline left in the buffer before re-displaying menu
            cout << "Press Enter to continue...";
            cin.get();
        }
    } while (choice != 6);

    return 0;
}
