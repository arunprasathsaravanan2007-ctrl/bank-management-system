#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Account
{
public:
    int accountNumber;
    string customerName;
    double balance;
};

void createAccount()
{
    Account a;

    cout << "\nEnter Account Number: ";
    cin >> a.accountNumber;
    cin.ignore();

    cout << "Enter Customer Name: ";
    getline(cin, a.customerName);

    cout << "Enter Initial Balance: ";
    cin >> a.balance;

    ofstream file("accounts.txt", ios::app);

    file << a.accountNumber << "|"
         << a.customerName << "|"
         << a.balance << endl;

    file.close();

    cout << "\nAccount Created Successfully!\n";
}

void displayAccounts()
{
    ifstream file("accounts.txt");

    string line;

    cout << "\n      ACCOUNT RECORDS      \n\n";

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}

void searchAccount()
{
    int searchAccountNo;

    cout << "\nEnter Account Number to Search: ";
    cin >> searchAccountNo;

    ifstream file("accounts.txt");

    string line;
    bool found = false;

    while (getline(file, line))
    {
        string temp = "";
        string data[3];
        int index = 0;

        for (char ch : line)
        {
            if (ch == '|')
            {
                data[index] = temp;
                index++;
                temp = "";
            }
            else
            {
                temp += ch;
            }
        }

        data[index] = temp;

        if (stoi(data[0]) == searchAccountNo)
        {
            cout << "\nAccount Found\n";
            cout << "Account Number : " << data[0] << endl;
            cout << "Customer Name  : " << data[1] << endl;
            cout << "Balance        : " << data[2] << endl;

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}

void depositMoney()
{
    int accountNo;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accountNo;

    cout << "Enter Deposit Amount: ";
    cin >> amount;

    ifstream file("accounts.txt");

    vector<string> records;
    string line;
    bool found = false;

    while (getline(file, line))
    {
        string temp = "";
        string data[3];
        int index = 0;

        for (char ch : line)
        {
            if (ch == '|')
            {
                data[index] = temp;
                index++;
                temp = "";
            }
            else
            {
                temp += ch;
            }
        }

        data[index] = temp;

        if (stoi(data[0]) == accountNo)
        {
            double balance = stod(data[2]);
            balance += amount;

            string newRecord =
                data[0] + "|" +
                data[1] + "|" +
                to_string(balance);

            records.push_back(newRecord);
            found = true;
        }
        else
        {
            records.push_back(line);
        }
    }

    file.close();

    ofstream outFile("accounts.txt");

    for (int i = 0; i < records.size(); i++)
    {
        outFile << records[i] << endl;
    }

    outFile.close();

    if (found)
        cout << "\nAmount Deposited Successfully!\n";
    else
        cout << "\nAccount Not Found!\n";
}

void withdrawMoney()
{
    int accountNo;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accountNo;

    cout << "Enter Withdrawal Amount: ";
    cin >> amount;

    ifstream file("accounts.txt");

    vector<string> records;
    string line;
    bool found = false;

    while (getline(file, line))
    {
        string temp = "";
        string data[3];
        int index = 0;

        for (char ch : line)
        {
            if (ch == '|')
            {
                data[index] = temp;
                index++;
                temp = "";
            }
            else
            {
                temp += ch;
            }
        }

        data[index] = temp;

        if (stoi(data[0]) == accountNo)
        {
            double balance = stod(data[2]);

            if (amount > balance)
            {
                cout << "\nInsufficient Balance!\n";
                records.push_back(line);
            }
            else
            {
                balance -= amount;

                string newRecord =
                    data[0] + "|" +
                    data[1] + "|" +
                    to_string(balance);

                records.push_back(newRecord);

                cout << "\nAmount Withdrawn Successfully!\n";
            }

            found = true;
        }
        else
        {
            records.push_back(line);
        }
    }

    file.close();

    ofstream outFile("accounts.txt");

    for (int i = 0; i < records.size(); i++)
    {
        outFile << records[i] << endl;
    }

    outFile.close();

    if (!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}

void checkBalance()
{
    int accountNo;

    cout << "\nEnter Account Number: ";
    cin >> accountNo;

    ifstream file("accounts.txt");

    string line;
    bool found = false;

    while (getline(file, line))
    {
        string temp = "";
        string data[3];
        int index = 0;

        for (char ch : line)
        {
            if (ch == '|')
            {
                data[index] = temp;
                index++;
                temp = "";
            }
            else
            {
                temp += ch;
            }
        }

        data[index] = temp;

        if (stoi(data[0]) == accountNo)
        {
            cout << "\nCurrent Balance : " << data[2] << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}

void deleteAccount()
{
    int accountNo;

    cout << "\nEnter Account Number to Delete: ";
    cin >> accountNo;

    ifstream file("accounts.txt");

    vector<string> records;
    string line;
    bool found = false;

    while (getline(file, line))
    {
        string temp = "";
        string data[3];
        int index = 0;

        for (char ch : line)
        {
            if (ch == '|')
            {
                data[index] = temp;
                index++;
                temp = "";
            }
            else
            {
                temp += ch;
            }
        }

        data[index] = temp;

        if (stoi(data[0]) == accountNo)
        {
            found = true;
        }
        else
        {
            records.push_back(line);
        }
    }

    file.close();

    ofstream outFile("accounts.txt");

    for (int i = 0; i < records.size(); i++)
    {
        outFile << records[i] << endl;
    }

    outFile.close();

    if (found)
        cout << "\nAccount Deleted Successfully!\n";
    else
        cout << "\nAccount Not Found!\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\nBANK MANAGEMENT SYSTEM\n\n";

        cout << "1. Create Account\n";
        cout << "2. Display Accounts\n";
        cout << "3. Search Account\n";
        cout << "4. Deposit Money\n";
        cout << "5. Withdraw Money\n";
        cout << "6. Check Balance\n";
        cout << "7. Delete Account\n";
        cout << "8. Exit\n\n";

        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createAccount();
            break;

        case 2:
            displayAccounts();
            break;

        case 3:
            searchAccount();
            break;

        case 4:
            depositMoney();
            break;

        case 5:
            withdrawMoney();
            break;

        case 6:
            checkBalance();
            break;

        case 7:
            deleteAccount();
            break;

        case 8:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 8);

    return 0;
}