#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 1. ABSTRACTION: Using an abstract class to define the interface
// The user doesn't need to know how transactions are stored, only that they can happen.
class IATM {
public:
    virtual void showMenu() = 0; // Pure virtual function
    virtual ~IATM() {}
};

// 2. ENCAPSULATION: Data is kept private and accessed via public methods
class Account {
private:
    float balance;
    int pin;
    vector<string> history;

public:
    Account(float initialBalance, int initialPin) 
        : balance(initialBalance), pin(initialPin) {}

    bool verifyPin(int enteredPin) {
        return enteredPin == pin;
    }

    void deposit(float amount) {
        if (amount > 0) {
            balance += amount;
            history.push_back("Deposited: " + to_string(amount) + " Rs");
            cout << "Successfully deposited " << amount << " Rs\n";
        } else {
            cout << "Invalid amount!\n";
        }
    }

    // 3. POLYMORPHISM: Overloading or simple logic for withdrawal
    virtual void withdraw(float amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            history.push_back("Withdrawn: " + to_string(amount) + " Rs");
            cout << "Successfully withdrawn " << amount << " Rs\n";
        } else {
            cout << (amount > balance ? "Insufficient balance!" : "Invalid amount!") << endl;
        }
    }

    void showBalance() {
        cout << "\nYour Balance: " << balance << " Rs\n";
        history.push_back("Checked Balance");
    }

    void showHistory() {
        if (history.empty()) {
            cout << "\nNo transactions yet.\n";
            return;
        }
        cout << "\n--- Transaction History ---\n";
        for (size_t i = 0; i < history.size(); i++) {
            cout << i + 1 << ". " << history[i] << endl;
        }
    }
};

// 4. INHERITANCE: ATM class inherits from the Interface and manages an Account
class ATM : public IATM {
private:
    Account* userAccount;

public:
    ATM(Account* acc) : userAccount(acc) {}

    void showMenu() override {
        int choice;
        float amount;

        while (true) {
            cout << "\n----- OOP MINI ATM -----\n";
            cout << "1. Check Balance\n2. Deposit\n3. Withdraw\n4. History\n5. Exit\n";
            cout << "Choose: ";
            cin >> choice;

            switch (choice) {
                case 1: userAccount->showBalance(); break;
                case 2: 
                    cout << "Enter deposit amount: "; cin >> amount;
                    userAccount->deposit(amount); 
                    break;
                case 3: 
                    cout << "Enter withdrawal amount: "; cin >> amount;
                    userAccount->withdraw(amount); 
                    break;
                case 4: userAccount->showHistory(); break;
                case 5: cout << "Exiting...\n"; return;
                default: cout << "Invalid choice!\n";
            }
        }
    }
};

int main() {
    Account myAcc(1000.0, 1234); // Creating an object
    ATM myATM(&myAcc);           // Injecting account into ATM

    int enteredPin, attempts = 0;
    while (attempts < 3) {
        cout << "Enter 4-digit PIN: ";
        cin >> enteredPin;
        if (myAcc.verifyPin(enteredPin)) {
            myATM.showMenu();
            return 0;
        } else {
            attempts++;
            cout << "Wrong PIN! Attempts left: " << 3 - attempts << endl;
        }
    }
    cout << "Account Locked!\n";
    return 0;
}
