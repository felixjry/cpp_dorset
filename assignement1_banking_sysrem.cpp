#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Account {
private:
    int accountNumber;
    string name;
    double balance;

public:
    Account(int accNo, string accName, double initialDeposit) {
        accountNumber = accNo;
        name = accName;
        balance = initialDeposit;
    }

    int getAccountNumber() { return accountNumber; }
    string getName() { return name; }
    double getBalance() { return balance; }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. New balance: " << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. Remaining balance: " << balance << endl;
            return true;
        } else {
            cout << "Insufficient balance or invalid amount." << endl;
            return false;
        }
    }

    void displayAccount() {
        cout << left << setw(10) << accountNumber << setw(20) << name << setw(10) << balance << endl;
    }
};

class BankingSystem {
private:
    vector<Account> accounts;

    Account* findAccount(int accNo) {
        for (auto &acc : accounts) {
            if (acc.getAccountNumber() == accNo) {
                return &acc;
            }
        }
        return nullptr;
    }

public:
    void createAccount(int accNo, string name, double initialDeposit) {
        if (findAccount(accNo) != nullptr) {
            cout << "Account number already exists!" << endl;
            return;
        }
        accounts.push_back(Account(accNo, name, initialDeposit));
        cout << "Account created successfully!" << endl;
    }

    void depositMoney(int accNo, double amount) {
        Account* acc = findAccount(accNo);
        if (acc) {
            acc->deposit(amount);
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void withdrawMoney(int accNo, double amount) {
        Account* acc = findAccount(accNo);
        if (acc) {
            acc->withdraw(amount);
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void transferMoney(int fromAccNo, int toAccNo, double amount) {
        Account* fromAcc = findAccount(fromAccNo);
        Account* toAcc = findAccount(toAccNo);

        if (fromAcc && toAcc) {
            if (fromAcc->withdraw(amount)) {
                toAcc->deposit(amount);
                cout << "Transfer successful!" << endl;
            }
        } else {
            cout << "One or both accounts not found!" << endl;
        }
    }

    void displayAllAccounts() {
        if (accounts.empty()) {
            cout << "No accounts found!" << endl;
            return;
        }
        cout << left << setw(10) << "Acc No" << setw(20) << "Name" << setw(10) << "Balance" << endl;
        cout << "------------------------------------------------------" << endl;
        for (auto &acc : accounts) {
            acc.displayAccount();
        }
    }
};

int main() {
    BankingSystem bank;
    int choice;

    do {
        cout << "\nBanking System Menu" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Transfer Money" << endl;
        cout << "5. Display All Accounts" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        int accNo, toAccNo;
        string name;
        double amount;

        switch (choice) {
            case 1:
                cout << "Enter Account Number: "; cin >> accNo;
                cout << "Enter Name: "; cin.ignore(); getline(cin, name);
                cout << "Enter Initial Deposit: "; cin >> amount;
                bank.createAccount(accNo, name, amount);
                break;
            case 2:
                cout << "Enter Account Number: "; cin >> accNo;
                cout << "Enter Deposit Amount: "; cin >> amount;
                bank.depositMoney(accNo, amount);
                break;
            case 3:
                cout << "Enter Account Number: "; cin >> accNo;
                cout << "Enter Withdrawal Amount: "; cin >> amount;
                bank.withdrawMoney(accNo, amount);
                break;
            case 4:
                cout << "Enter Sender Account Number: "; cin >> accNo;
                cout << "Enter Receiver Account Number: "; cin >> toAccNo;
                cout << "Enter Transfer Amount: "; cin >> amount;
                bank.transferMoney(accNo, toAccNo, amount);
                break;
            case 5:
                bank.displayAllAccounts();
                break;
            case 6:
                cout << "Exiting Banking System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
