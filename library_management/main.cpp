#include <bits/stdc++.h>

using namespace std;
//book class

class Book{
    private:
        int Bookid;
        char title[100];
        char author[50];
        bool isIssued;
        int issuedToMemberID; // NEW: Tracks who has the book

    public:
        void create_book(){
            cout<<"\nEnter the Book ID: ";
            cin>>Bookid;
            cin.ignore();

            cout<<"Enter Book Title: ";
            cin.getline(title,100);

            cout<<"Enter Book's Author: ";
            cin.getline(author,50);

            isIssued=false; // A new book is not issued by default
            issuedToMemberID=0; //initially, book is not issued by anyone(currently in library)

        }

        // Function to display book details
        void show_book() {
            cout << "\nBook ID: " << Bookid;
            cout << "\nTitle: " << title;
            cout << "\nAuthor: " << author;
            if (isIssued) {
                cout << "\nStatus: Issued to Member ID #" << issuedToMemberID << endl;
            } 
            else {
                cout << "\nStatus: Available on shelf" << endl;
            }
        } 
        
        // Getters for file handling and searching
        int  get_id() { return Bookid; }
        char* get_title(){return title;}
        char* get_author(){return author;}
        bool get_status() { return isIssued; }
        int get_memberid(){ return issuedToMemberID; }
    
        // NEW: Setter to link the book to a member when issued
        void issue_to_member(int member_id) {
            isIssued = true;
            issuedToMemberID = member_id;
        }

        // NEW: Setter to unlink the book when returned
        void return_to_library() {
            isIssued = false;
            issuedToMemberID = 0;
        }

};

//member class

class Member{
    private:
        int MemberId;
        char name[50];

    public:
        
        void create_member() {
            cout << "\nEnter Member ID: ";
            cin >> MemberId;
            cin.ignore();
        
            cout << "Enter Member Name: ";
            cin.getline(name, 50);
        }

        void show_member() {
            cout << "\nMember ID: " << MemberId;
            cout << "\nName: " << name << endl;
        }

        int get_id() { return MemberId; }
};

//file handling Functions
void write_book(){
    Book bk;
    ofstream outfile;
    outfile.open("book.dat",ios::binary | ios::app);
    bk.create_book();
    outfile.write(reinterpret_cast<char *>(&bk),sizeof(Book));
    outfile.close();

}

void write_member(){
    Member mb;
    ofstream outfile;
    outfile.open("member.dat",ios::binary | ios::app);
    mb.create_member();
    outfile.write(reinterpret_cast<char *>(&mb),sizeof(Member));
    outfile.close();

}

//option: 1-> issue a book and   2-> returning a book
void modify_book(int n,int option){
    bool found=false;
    Book bk;
    ifstream infile;
    ofstream temp;
    infile.open("book.dat",ios::binary);
    temp.open("temp.dat",ios::binary);

    if(!infile.is_open() || !temp.is_open()){
        cout<<"ERROR : File could'nt be opened ";
        return;
    }

    while(infile.read(reinterpret_cast<char *>(&bk),sizeof(Book))){
        if(bk.get_id() == n){
           if(option == 1){ //issuing a book
                if(bk.get_status()){
                    cout<<"Sorry: This Book is already Being Issued to #"<<bk.get_memberid()<<endl;
                }
                else{
                    cout<<"Okay: You can Issue this Book: \n";
                    cout<<"Enter Your Member ID: ";
                    int ID;
                    cin>>ID;
                    bk.issue_to_member(ID);
                    cout<<"Successfully The Book is Being issued by #"<<ID;

                }
                
           }

           else if(option == 2){ //returning a book
                if(bk.get_status()){   
                    cout<<"Enter Your Member ID: ";
                    int ID;
                    cin>>ID;
                    if(bk.get_memberid() == ID){
                        bk.return_to_library();
                        cout<<"Thank You For Returning The book ";
                    }
                    else{
                        cout<<"Entered a wrong member ID ";
                    }
                    
                }
                else{
                    cout<<"There is a misunderstanding as this Book is not being Issued: ";
                }
           }

           found=true;
           cout<<"\n\nRecord Updated: ";

        }

        temp.write(reinterpret_cast<char *>(&bk),sizeof(Book));
    }

    infile.close();
    temp.close();

    if(found){
            remove("book.dat");
            rename("temp.dat","book.dat");

        }
    else{
            remove("temp.dat");
            cout << "\n\n Record Not Found ";
    }

}

void display_all_books(){
    Book bk;
    ifstream infile;
    infile.open("book.dat",ios::binary);

    if(!infile.is_open()){
        cout<<"ERROR: File couldn't be opened ";
        return;
    }

    cout << "\n\n=======================================";
    cout << "\n         LIBRARY BOOK DATABASE         ";
    cout << "\n=======================================";

    while (infile.read(reinterpret_cast<char *>(&bk), sizeof(Book))) {
        bk.show_book();
        cout << "\n---------------------------------------";
    }

    infile.close();
}

void search_book(){
    Book bk;
    char search_term[100]; //can be title or author anything
    ifstream infile;
    bool found=false;

    cout << "\nEnter Book Title or Author to search: ";
    cin.ignore(); // Clear the input buffer
    cin.getline(search_term, 100);

    infile.open("book.dat",ios::binary);

    if (!infile.is_open()) {
        cout << "\nFile could not be opened!.";
        return;
    }

    while(infile.read(reinterpret_cast<char *>(&bk),sizeof(Book))){
        // strstr checks if search_term exists inside the title OR the author
        if (strstr(bk.get_title(), search_term) || strstr(bk.get_author(), search_term)) {
            bk.show_book();
            cout << "\n----------------------";
            found = true;
        }
    }

    infile.close();

    if (!found) {
        cout << "\n\nNo books found matching: " << search_term;
    }

}







int main() {
    int choice;
    int ID;
    

    do {
        cout << "\n\n=== LIBRARY MANAGEMENT SYSTEM ===";
        cout << "\n1. Add a New Book";
        cout << "\n2. Add a New Member";
        cout << "\n3. Issue a Book";
        cout << "\n4. Return a Book";
        cout << "\n5. Search for a Book (by Title/Author)";
        cout << "\n6. Display All Books";
        cout << "\n7. Exit";
        cout << "\n=================================";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n-- ADD NEW BOOK --\n";
                write_book();
                break;
                
            case 2:
                cout << "\n-- ADD NEW MEMBER --\n";
                write_member();
                break;
                
            case 3:
                cout << "\n-- ISSUE BOOK --\n";
                cout<<"Enter the Book ID: ";
                cin>>ID;
                modify_book(ID,1);
                break;
                
            case 4:
                cout << "\n-- RETURN BOOK --\n";
                cout<<"Enter the Book ID: ";
                cin>>ID;
                modify_book(ID,2);
                break;
                
            case 5:
                cout << "\n-- SEARCH BOOK --\n";
                search_book();
                break;
                
            case 6:
                cout << "\n-- ALL BOOKS --\n";
                display_all_books();
                break;
                
            case 7:
                cout << "\nExiting Library System. Goodbye!\n";
                break;
                
            default:
                cout << "\nInvalid choice. Please try again.";
        }
    } while (choice != 7);

    return 0;
}


