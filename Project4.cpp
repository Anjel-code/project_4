#include "Project4.h"
using namespace std;

// Global Variables
list<Account> accounts;
list<Account>::iterator itr;
int Account::nextAccNum = 1000; //initializing the static variable to a 1000

// Functions
void printOptions()
{
    //Printing all options
    cout << "\n";
    cout << "+-----------------------------------------------+" << endl;
    cout << "| 1.\tOpen new account                        |" << endl;
    cout << "| 2.\tDeposit into account                    |" << endl;
    cout << "| 3.\tWithdraw from account                   |" << endl;
    cout << "| 4.\tFast transfer $40 into account          |" << endl;
    cout << "| 5.\tPrint a list of all accounts            |" << endl;
    cout << "| 6.\tEnd transaction (exit)                  |" << endl;
    cout << "+-----------------------------------------------+" << endl;
}

// Formating Function For Account Listing
void addSpaces(int numSpaces)
{
    // Function will output spaces only if the name is withing a certain length, otherwise there is no point in formating
    if (numSpaces > 0)
    {
        for (int i = 0; i < numSpaces; i++)
        {
            cout << " ";
        }
    }

    else
    {
        return;
    }
}

void openAccount()
{
    //User Input Variables
    string accName;
    float initDeposit;

    //Ignoring \n character in the buffer to avoid prompt skipping
    cin.ignore();
    cout << "Enter customer account name: ";
    getline(cin, accName);
    cout << "Enter initial deposit amount: $";
    cin >> initDeposit;

    //Checking initial deposit amount
    if(initDeposit < 0) {
        cout << "Error: Invalid deposit amount. Operation failed." << endl;
        return;
    }

    //Creating new instance(object) of the Account Class
    Account newCustomer = Account(accName, initDeposit);

    // Formating float output to 2 decimals
    cout << fixed << setprecision(2);
    cout << "Account openend: " << newCustomer.getAccNum() << " " << newCustomer.getAccName() << ": $" << newCustomer.getAccBalance();

    // Storing account into our "database"(vector) of created accounts
    accounts.push_back(newCustomer);
}

void makeDeposit()
{
    //User Input Variables
    int num;
    float amount;

    cout << "Enter account number: ";
    cin >> num;

    // Searching for account number inside vector
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        //Checking whether the vector's element private variable accNum is equal to the searched account number
        if ((*itr).getAccNum() == num)
        {
            cout << "Enter deposit amount: ";
            cin >> amount;

            //Checking the deposit amount
            if(amount < 0) {
                cout << "Error: Invalid deposit amount. Operation failed." << endl;
                return;
            }

            //Mutating accBalance variable if the condition is true.
            (*itr).setAccBalance(((*itr).getAccBalance() + amount));

            //Formating float output to 2 decimals
            cout << "Deposit accpeted for account " << ((*itr)).getAccNum() << " : $" << fixed << setprecision(2) << (*itr).getAccBalance() << endl;
            //Interrupting the function after successful deposit transaction
            return;
        }
    }
    //If the loop completed successfully, informing user that the account was not found
    cout << "Error: Account number not found. Operation failed.";
}

void makeWithdrawal()
{
    //User Input Variables
    int num;
    string name;
    float amount;

    cout << "Enter account number: ";
    cin >> num;
    cin.ignore();

    cout << "Enter account name for security purpose: ";
    getline(cin, name);

    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        //Checking whether the vector's element private variable accNum is equal to the search account number
        if ((*itr).getAccNum() == num && (*itr).getAccName() == name)
        {
            cout << "Enter withdrawal amount: $ ";
            cin >> amount;
            
            //Checking whether the difference of vector's private variable accBalance and user input is greater than or equal to zero
            if(((*itr).getAccBalance() - amount) >= 0 and amount > 0) {
                //If the condition is true, mutating private variable accBalance
                (*itr).setAccBalance(((*itr).getAccBalance() - amount));

                // formating float output to 2 decimals
                cout << fixed << setprecision(2);
                cout << "Withdrawal processed for account " << (*itr).getAccNum() << " : " << (*itr).getAccBalance() << endl;
                //Interrupting function
                return;
            }

            //if the condition is false, throwing a runtime error
            else {
                throw runtime_error("Runtime error: Insufficient funds. Operation failed.");
            }
        }
    }

    //If the loop completed successfully, throwing an invalid argument error
    throw invalid_argument("Invalid argument: Account number and name do not match, or account not found. Access denied.");
}

void fastTransfer() {
    // throw runtime_error("message");
    throw runtime_error("Fast transfer feature is currently disabled");
}

void printAccounts()
{
    //Ensuring that there is at least one account in the vector
    if (accounts.size() > 0)
    {
        //Static part of the table
        cout << "+-----------------------------------------------+" << endl;
        cout << "| Account number | Name\t\t| Balance\t|" << endl;
        cout << "+-----------------------------------------------+" << endl;

        //Iterating over each account in the vector
        for (itr = accounts.begin(); itr != accounts.end(); itr++)
        {
            //Outputing current vector's element info
            cout << "|           " << (*itr).getAccNum() << " | " << (*itr).getAccName();
            // Adding a certain amount of spaces based on the length of the account name
            addSpaces((12 - (*itr).getAccName().length()));
            cout << " | $ " << fixed << setprecision(2) << (*itr).getAccBalance();
            // Adding a certain amount of spaces based on the length of the account balance casted to a string
            addSpaces((16 - to_string((*itr).getAccBalance()).length()));
            cout << "|" << endl;
        }

        //Static part of the table
        cout << "+-----------------------------------------------+" << endl;
    }

    else {
        //If there are no accounts, informing user
        cout << "The accounts list is empty.";
    }
}

int main()
{
    //Header
    cout << "+-------------------------------------------------+" << endl;
    cout << "|         Computer Science and Engineering        |" << endl;
    cout << "|        CSCE 1040 - Computer Programming II      |" << endl;
    cout << "|    Anzhel Pak   ap1847   anzhelpak@my.unt.edu   |" << endl;
    cout << "+-------------------------------------------------+" << endl;

    int choice = 0;

    // User Interactive Interface Iterative Logic
    while (true)
    {
        printOptions();
        cin >> choice;

        //Using switch-case in order to achive menu prompt functionality
        switch (choice)
        {
        case 1:
            openAccount();
            continue; //Instead of exiting the loop we go back to the beginning
        case 2:
            makeDeposit();
            continue;
        case 3:
            try {
                makeWithdrawal();
            }
            catch(const invalid_argument& e) {
                cout << e.what() << endl;
            }
            catch(const runtime_error& e) {
                cout << e.what() << endl;
            }

            continue;
        case 4:
            try {
                fastTransfer();
            }
            catch(const runtime_error& e) {
                cout << "Error: " << e.what() << endl;
                continue;
            }
        case 5:
            printAccounts();
            continue;
        case 6:
            // exiting the Swtich-Case block
            cout << "Thank you for your business!" << endl;
            break;
        default:
            cout << "Invalid option, please try again." << endl;
            continue;
        }

        // Exiting the loop
        break;
    }

    return 0;
}