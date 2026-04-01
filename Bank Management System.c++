#include <iostream>
using namespace std;

// Base Class
class Account {
protected:
    int accNo;
    string name;
    double balance;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    virtual void deposit() {
        double amt;
        cout << "Enter amount to deposit: ";
        cin >> amt;
        balance += amt;
        cout << "Deposited Successfully!\n";
    }

    virtual void withdraw() {
        double amt;
        cout << "Enter amount to withdraw: ";
        cin >> amt;

        if (amt <= balance) {
            balance -= amt;
            cout << "Withdraw Successful!\n";
        } else {
            cout << "Insufficient Balance!\n";
        }
    }

    virtual void display() {
        cout << "\nAccount No: " << accNo;
        cout << "\nName: " << name;
        cout << "\nBalance: " << balance << endl;
    }
};

// Derived Class - Savings
class Savings : public Account {
public:
    void display() override {
        cout << "\n--- Savings Account ---";
        Account::display();
    }
};

// Derived Class - Current
class Current : public Account {
public:
    void withdraw() override {
        double amt;
        cout << "Enter amount to withdraw: ";
        cin >> amt;

        if (amt <= balance + 1000) { // overdraft
            balance -= amt;
            cout << "Withdraw Successful (Overdraft allowed)!\n";
        } else {
            cout << "Limit Exceeded!\n";
        }
    }

    void display() override {
        cout << "\n--- Current Account ---";
        Account::display();
    }
};

// Main Menu
int main() {
    Savings s;
    Current c;

    int choice, type;

    do {
        cout << "\n\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 4) {
            cout << "Select Account Type (1: Savings, 2: Current): ";
            cin >> type;
        }

        switch (choice) {
        case 1:
            if (type == 1)
                s.createAccount();
            else
                c.createAccount();
            break;

        case 2:
            if (type == 1)
                s.deposit();
            else
                c.deposit();
            break;

        case 3:
            if (type == 1)
                s.withdraw();
            else
                c.withdraw();
            break;

        case 4:
            if (type == 1)
                s.display();
            else
                c.display();
            break;

        case 5:
            cout << "Thank you!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}
