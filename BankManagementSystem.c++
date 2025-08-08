#include<iostream>
#include<fstream>//for file operations
#include"json.hpp"//for JSON handling
#include<vector>
using json = nlohmann::json;//to simplify syntax
using namespace std;
class BankAccount{
    private:
        string Password;
        string AccountNumber;
        string AccountHolderName;
        double Balance;
    public:
        BankAccount(string AccountNumber,string AccountHolderName,double Balance,string Password){//Parameterized Constructor
            this->AccountNumber = AccountNumber;
            this->AccountHolderName = AccountHolderName;
            this->Balance = Balance;
            this->Password = Password;
        }

        //function declarations
        void Deposit(double amount);
        void withdraw(double amount);
        void ShowBalance()const;//Showing balance not accepting any parameter of balance or amount to modify the value inside the function
        bool verifyPassword(const string& inputPassword)const;//passing the refrence of the password not a copy and not allowed to modify the 
        
        //getter function
        string getAccountNumber()const;
        string getAccountHolderName()const;
        string getAccountPassword()const;
        double getBalance()const;
};
string BankAccount::getAccountNumber()const{
    return AccountNumber;
}
string BankAccount::getAccountHolderName()const{
    return AccountHolderName;
}
string BankAccount::getAccountPassword()const{
    return Password;
}
double BankAccount::getBalance()const{//For internal code calculations
    return Balance;
}
void BankAccount::ShowBalance()const{//User-friendly (Scope resolution used for outside class functions)
    cout<<"Balance: ₹"<<Balance<<endl;
}
bool BankAccount::verifyPassword(const string& inputpassword)const{//return the bool value after verifying the password
    return inputpassword==Password;
}
void BankAccount::Deposit(double amount){//deposit function for the BankAccount
    if(amount>0){
        Balance+=amount;
        cout<<"₹"<<amount<<" is succesfully deposited in your bank account.\n";
    }
    else{
        cout<<"Invalid Deposit.\n";
    }
}
void BankAccount::withdraw(double amount){
    if (amount>Balance){
        cout<<"Insufficient Balance.\n";
    }
    else if(amount<=0){
        cout<<"Invalid Withdrawl\n";
    }
    else{
        Balance-=amount;
        cout << "₹" << amount << " is withdrawn successfully.\n";
    }
}
class Bank{
    private:
        vector<BankAccount>accounts;//Holds the Bank Account number for different users
    
    public:
        void createAccounts();//Create new Accounts for the new Users
        BankAccount* login(const string&AccountNumber,const string&password);//
        void loginSession(BankAccount* user);
        void saveAccountToFile();//declare the accounts to json files
        void loadAccountsFromfile();//load all the accounts details from json and passes to the accounts vector
        void transferAmount(BankAccount* sender);
};
void Bank::createAccounts(){
    string accNo,name,password;
    double InitialDeposit;

    cout<<"\n--- Create Account ---\n";
    cout<<"Enter the Account Number: ";
    cin>>accNo;

    //Check if the Account already Exists
    for(auto&acc:accounts){//For-each loop for quick check for account number
        if(acc.getAccountNumber()==accNo){
            cout<<"Account Already Exist!!"<<endl;
            return;
        }
    }

    cout<<"Enter the Account Holder Name: "<<endl;
    cin.ignore();//flush new line
    getline(cin,name);

    cout<<"Enter the Initial Deposit: ";
    cin>>InitialDeposit;//Initial Deposit

    cout<<"Set Account Password: ";
    cin>>password;

    BankAccount NewAccount(accNo,name,InitialDeposit,password);
    accounts.push_back(NewAccount);
    saveAccountToFile();//saves all the data in the format of json
    cout<<"Account Created Succesfully!\n";
}
BankAccount* Bank::login(const string &accNo,const string &password){
    for(auto &acc:accounts){
        if(acc.getAccountNumber()==accNo && acc.verifyPassword(password)){
            return &acc;
        }
    }
    return nullptr;
}
void Bank::loginSession(BankAccount* user){
    int Choices;
    double amount;

    do
    {
        cout<<"\nLogged In as: "<<user->getAccountHolderName()<<"\n"
            <<"(Account No: "<<user->getAccountNumber()<<")\n";
        cout<<"1. Deposit\n";
        cout<<"2. Withdraw\n";
        cout<<"3. Show Balance\n";
        cout<<"4. Bank to Bank Transfer\n";
        cout<<"0. Logout\n";
        cout<<"Enter your Choice: ";
        cin>>Choices;

        switch (Choices)
        {
        case 1:
            cout<<"Enter Amount to Deposit: "<<endl;
            cin>>amount;
            user->Deposit(amount);
            cout<<"New Balance: ₹"<<user->getBalance()<<endl;
            saveAccountToFile();//Save changes after withdraw
            break;
        case 2:
            cout<<"Enter amount to Withdraw: "<<endl;
            cin>>amount;
            user->withdraw(amount);
            cout<<"New Balance: ₹"<<user->getBalance()<<endl;
            saveAccountToFile();//save changes after deposit
            break;
        case 3:
            user->ShowBalance();
            break;
        case 4:
            transferAmount(user);
            break;
        case 0:
            cout<<"Loging Out...\n";
            break;
        default:
            cout<<"Invalid Choices!!"<<endl;
            break;
        }
    } while (Choices!=0);
}
void Bank::saveAccountToFile(){//accounts to JSON file format
    json jaccounts = json::array();
    for(const auto&acc:accounts){
        jaccounts.push_back({
            {"AccountNumber",acc.getAccountNumber()},
            {"AccountHolderName",acc.getAccountHolderName()},
            {"Balance",acc.getBalance()},
            {"Password",acc.getAccountPassword()}
            //We don't save passwords in the form of Hashing/Hash Codes but later on these changes will be made
        });
    }
    ofstream outfile("accounts.json");//file name and format where all data is saving
    outfile<<jaccounts.dump(4);//pretty print with identations
    outfile.close();

    cout<<"Accounts saved to file successfully.\n";
}
void Bank::loadAccountsFromfile(){//opens the accounts json and sends the data to the accounts vector
    ifstream infile("accounts.json");
    if(!infile.is_open()){//if no file found or no data is present then below message is shown
        cout<<"No saved accounts found.\n";
        return;
    }

    json jaccounts;
    infile>>jaccounts;//Read JSON from the file

    accounts.clear();//Clear existing accounts details to avoid duplicates

    for(const auto&jAcc:jaccounts){
        string accno = jAcc["AccountNumber"];
        string HolderName = jAcc["AccountHolderName"];
        double balance = jAcc["Balance"];
        string password = jAcc["Password"];//Sotring Orignal password instead of default for login system
        
        BankAccount acc(accno,HolderName,balance,password);
        accounts.push_back(acc);
    }
}
void Bank::transferAmount(BankAccount* sender){
    string reciverAccno;
    double Amount;

    cout<<"Enter the recive Account Number: ";
    cin>>reciverAccno;
    
    //check if reciver is same as senders
    if(reciverAccno==sender->getAccountNumber()){
        cout<<"Same Account, Money cannot be transfered.";
        return;
    }

    //search for in the already stored data of the bankaccounts
    BankAccount* reciver = nullptr;
    for(auto &acc:accounts){
        if(acc.getAccountNumber()==reciverAccno){
            reciver = &acc;
            break;
        }
    }

    //if reciver account number not found in the account data
    if(reciver==nullptr){
        cout<<"Reciver Account Not Found\n";
        return;
    }

    cout<<"Enter the amount to transfer: \n";
    cin>>Amount;
    
    //Ask amount to transfer
    if(Amount<=0){
        cout<<"Invalid Amount to transfer"<<endl;
        return;
    }
    
    //Amount greater than sender's account balance
    if(sender->getBalance()<Amount){
        cout<<"Insufficient Balance!"<<endl;
        return;
    }

    //Perform Amount transfer to the ansked account
    sender->withdraw(Amount);
    reciver->Deposit(Amount);

    cout<<"₹"<<Amount<<" transfered to Account No: "<<reciverAccno<<endl;

    //Save updated accounts to JSON
    saveAccountToFile();
}
int main(){
    Bank mybank;
    mybank.loadAccountsFromfile(); //<== This line is important for loading all the save data 
    int mainChoices;

    cout<<"Welcome to K-P-S Bank System\n";

    do
    {
        cout<<"\nmain menu\n";
        cout<<"1. Create Account\n";
        cout<<"2. Login to Account\n";
        cout<<"0. Exit\n";
        cout<<"Enter your Choices: ";
        cin>>mainChoices;

        switch (mainChoices)
        {
        case 1:
            mybank.createAccounts();
            break;
        case 2:
            {
                string accNo,Password;
                cout<<"Enter the Account Number: ";
                cin>>accNo;
                cout<<"Enter the Account Password: ";
                cin>>Password;

                BankAccount* user = mybank.login(accNo,Password);
                if (user){
                    mybank.loginSession(user);
                }
                else{
                    cout<<"Invalid Credentials!\n";
                }
                break;
            }
        case 0:
            cout<<"Thank you for using our Bank System!\n";
            break;
        default:
            cout<<"Invalid Choices.\n";
        }
    } while (mainChoices!=0);
    return 0;
}