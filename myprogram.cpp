#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

class BankAccount{
    private:
        string accountNumber;
        int pin;
        double balance;
    
    public:
        BankAccount(string accNum,int p, double bal){
            accountNumber=accNum;
            pin=p;
            balance=bal;
        }
        
        bool authenticate(int enteredPin){
            return pin==enteredPin;
        }

        void displayBalance(){
            cout << "     ACCOUNT BALANCE   \n";
            cout << "\n";
            cout << "Current Balance: ₹" << fixed <<setprecision(2) << balance << endl;
            cout << "\n";
        }

        void deposit(double amount){
            balance +=amount;
            cout<< "\n Deposit successful! \n";
            displayBalance();
        }

        void withdraw(double amount){
            if(amount >balance){
                cout<< "\n Insufficient funds! \n";
            }
            else{
                balance-=amount;
                cout << "\n Withdrawal Successful! \n";
                displayBalance();
            }
        }

};

class ATM{
    public:
        void startATM(BankAccount &account){
            int pin,choice;

            cout << " \n Welcome to the our ATM \n";
            cout << " ENTER PIN: ";
            cin>> pin;
            if(!account.authenticate(pin)){
                cout << "\n Invalid PIN! \n";
                return;
            }

            do{
                cout << "\n===================================\n";
                cout << "           MAIN MENU           \n";
                cout << "===================================\n";
                cout << "1  Check Balance\n";
                cout << "2  Deposit Money\n";
                cout << "3  Withdraw Money\n";
                cout << "4  Exit\n";
                cout << "===================================\n";
                cout << "Enter your choice: ";
                cin >> choice;

                if(cin.fail()){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "\n Invalid Input! Please enter a valid choice";
                    continue;
                }

                if(choice==1){
                    account.displayBalance();
                }
                else if(choice==2){
                    double amount;
                    cout<<"\n Enter deposit amount: ₹";
                    cin >>amount;
                    if(amount>0){
                        account.deposit(amount);
                    }
                    else{
                        cout << "\n Invalid Amount! \n";
                    }
                }
                else if(choice==3){
                    double amount;
                    cout << "\n Enter withdrawal amount: ₹";
                    cin >> amount;
                    if(amount>0){
                        account.withdraw(amount);
                    }
                    else{
                        cout << "\n Invalid Amount! \n";
                    }
                }
                else if(choice==4){
                    cout << "\n Thank you for using the ATM! \n";
                    break;
                }
                else{
                    cout << "\n Invalid Choice! \n";
                }
            }while(true);
        }
};

int main(){
    BankAccount myAccount("246893",3452,4000);
    ATM myatm;
    myatm.startATM(myAccount);
    return 0;
}

