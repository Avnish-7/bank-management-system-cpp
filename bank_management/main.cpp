
#include <bits/stdc++.h>

using namespace std;

class BankAccount {
    private:
    int acno;
    char name[50]; 
    double balance;

    public:
        void create_account(){
            cout<<"\nEnter the Account number: ";
            cin>>acno;
            cin.ignore();
            cout<<"Enter the Account's Holder Name: ";
            cin.getline(name,50);
            cout<<"Enter the Initial Balance: ";
            cin>>balance;
            cout<<"\nAccount Created Successfully!";

        }

        void show_account(){
            cout << "\nAccount Number: " << acno;
            cout << "\nAccount Holder Name: " << name;
            cout << "\nBalance: $" << fixed << setprecision(2) << balance << "\n";
        }

        void deposit(double amt) {
            balance += amt;
        }

        void withdraw(double amt) {
            if (amt > balance) {
                cout << "\nInsufficient Funds! Transaction Cancelled.\n";
            } 
            else {
                balance -= amt;
                cout << "\nWithdrawal Successful!\n";
            }
        }

        int get_acno() const {
            return acno;
        }

        double get_balance() const {
            return balance;
        }
    };

    
    // --- File Handling Functions ---

    //1. Function to write new record to file
    void write_account(){
        BankAccount ac;
        ofstream outfile;
        outfile.open("bank_records.dat",ios::binary | ios::app);
        ac.create_account();
        outfile.write(reinterpret_cast<char *>(&ac),sizeof(BankAccount));
        outfile.close();
    }

    //2. Function to search for an account and display it
    void display_account(int n){
        BankAccount ac;
        bool found=false;
        ifstream infile;
        infile.open("bank_records.dat",ios::binary);

        if(!infile.is_open()){
            cout<<"File couldn't be opened";
            return;
        }

        while(infile.read(reinterpret_cast<char *>(&ac),sizeof(BankAccount))){
            if(ac.get_acno() == n){
                ac.show_account();
                found=true;
                break;

            }
        }
        infile.close();

        if(!found){
           cout<<"\n\nAccount number does not exist.";
        }
    }
    
    //3.Function to deposit or withdraw (Modifies the file)
    //option-> 1 -> deposit and 2 -> withdraw
    void modify_account(int n,int option){
        bool found = false;
        BankAccount ac;
        fstream file;
        file.open("bank_records.dat",ios::binary | ios::in | ios::out);

        if(!file.is_open()) {
        cout << "File could not be opened! Press any key...";
        return;
        }

        while(file.read(reinterpret_cast<char *>(&ac),sizeof(BankAccount))){
            if(ac.get_acno() == n){
                ac.show_account();
                if(option == 1){
                    cout << "\n\n--- DEPOSITING AMOUNT ---";
                    cout << "\nEnter The amount to be deposited: $";
                    double amt;
                    cin >> amt;
                    ac.deposit(amt);
                }
                else if(option == 2) {
                cout << "\n\n--- WITHDRAWING AMOUNT ---";
                cout << "\nEnter The amount to be withdrawn: $";
                double amt;
                cin >> amt;
                ac.withdraw(amt);
                }
                //by moving the cursor back then overwrite the old one from the updated one
                int pos = (-1) * static_cast<int>(sizeof(BankAccount));
                file.seekp(pos, ios::cur); // Move the write pointer back by one object size
            
                // Overwrite the old object with the newly updated object
                file.write(reinterpret_cast<char *>(&ac), sizeof(BankAccount));
                cout << "\n\n Record Updated";
                found = true;
            }
        }
        file.close();
        if(found == false) {
            cout << "\n\n Record Not Found ";
        }
    }

    //one more way to write modify function-> using two files  temp and fin to write and read respectively
    void modify_acc(int n,int option){
        bool found=false;
        BankAccount ac;
        ifstream fin;
        ofstream temp;
        fin.open("bank_records.dat",ios::binary);
        temp.open("temp.dat",ios::binary);

        if(!fin.is_open() || !temp.is_open()){
            cout<<"File couldn't be opened ";
            return;
        }

        while(fin.read(reinterpret_cast<char *>(&ac),sizeof(BankAccount))){

            if(ac.get_acno() == n){
                if(option == 1){
                    cout << "\n\n--- DEPOSITING AMOUNT ---";
                    cout << "\nEnter The amount to be deposited: $";
                    double amt;
                    cin >> amt;
                    ac.deposit(amt);
                }

                else if(option == 2) {
                cout << "\n\n--- WITHDRAWING AMOUNT ---";
                cout << "\nEnter The amount to be withdrawn: $";
                double amt;
                cin >> amt;
                ac.withdraw(amt);
                }

                cout << "\n\n Record Updated";
                found = true;
                
            }

            temp.write(reinterpret_cast<char *>(&ac),sizeof(BankAccount));
        }  

        fin.close();
        temp.close();

        if(found){
            remove("bank_records.dat");
            rename("temp.dat","bank_records.dat");

        }
        else{
            remove("temp.dat");
            cout << "\n\n Record Not Found ";
        }
    }

int main(){
        int choice;
        int num;

        do{
            cout << "\n\n================================";
            cout << "\n    BANK MANAGEMENT SYSTEM";
            cout << "\n================================";
            cout << "\n1. Create New Account";
            cout << "\n2. Deposit Money";
            cout << "\n3. Withdraw Money";
            cout << "\n4. Check Balance";
            cout << "\n5. Exit";
            cout << "\n\nSelect Your Option (1-5): ";
            cin >> choice;
            switch(choice){
                case 1: write_account();
                        break;

                case 2: 
                        cout<<"\n\nEnter the Account Number: ";
                        cin >> num;
                        modify_acc(num, 1);
                        break;

                case 3:
                        cout << "\n\nEnter Account Number: ";
                        cin >> num;
                        modify_acc(num, 2);
                        break;

                case 4:
                        cout << "\n\nEnter Account Number: ";
                        cin >> num;
                        display_account(num);
                        break;

                case 5:
                        cout << "\nExiting System. Thank you!\n";
                        break;
                default:
                        cout << "\nInvalid Option! Please try again.\n";

            }
        }while (choice != 5);
        
        return 0;
}
