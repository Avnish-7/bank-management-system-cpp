
#include <bits/stdc++.h>

using namespace std;

// Defining the student structure
struct Student {
    int rollNumber;
    string name;
    string department;
};

// --- Function Prototypes ---
void addStudent() {
    Student NewStudent;

    //enter the details of student
    cout<<"<\n--- STUDENT DETAILS --->\n";
    cout<<"Enter Roll number: ";
    cin>>NewStudent.rollNumber;

    //Clear the input buffer before reading strings with spaces
    cin.ignore();

    cout<<"Enter Student Name: ";
    getline(cin,NewStudent.name);

    cout<<"Enter Student Department: ";
    getline(cin,NewStudent.department);

    ofstream fout("students.txt",ios::app); //we want to append , dont want to overwrite the contents
    
    if(fout.is_open()){
        fout<<NewStudent.rollNumber<<","
            <<NewStudent.name<<","
            <<NewStudent.department<<"\n";

        fout.close();
        cout << "Success: Student record saved to file!\n";
    }

    else{
        cout<<"Error: Could not open the file for writing.\n";
    }

    cout << "Add Students function called.\n";

}

void displayStudents() {

    cout<<"\n<---Displaying Student Details--->\n";

    ifstream fin("students.txt");

    if (!fin.is_open()) {
        cout << "Error: Could not open files.\n";
        return;
    }

    string line;

    while(getline(fin,line)){
        cout<<line<<endl;
    }
    fin.close();
    cout << "Display Students function called.\n";
}

void updateStudent() {
    
    int targetRoll;
    cout << "\n<--- Update Student --->\n";
    cout << "Enter the Roll Number to update: ";
    cin >> targetRoll;
    cin.ignore(); // Clear buffer for upcoming getlines!
    
    ifstream fin("students.txt");
    ofstream tempFile("temp.txt");

    // Check if files opened properly
    if (!fin.is_open() || !tempFile.is_open()) {
        cout << "Error: Could not open files.\n";
        return;
    }

    string line;
    bool found=false;

    while(getline(fin,line)){
        // Use stringstream to break the line apart at the commas
        stringstream ss(line);
        string rollStr;

        // Get the first chunk of text up to the first comma (the roll number)
        getline(ss, rollStr, ',');

        if(stoi(rollStr) == targetRoll){
            found=true;
            Student UpdatedStudent;
            UpdatedStudent.rollNumber=targetRoll;

            cout<<"Student Found! -- Enter the details: "<<endl;
            cout<<"Enter new name: ";
            getline(cin,UpdatedStudent.name);
            cout<<"Enter new department: ";
            getline(cin,UpdatedStudent.department);

            //Replace specific record: Write the NEW data to the temp file
            tempFile << UpdatedStudent.rollNumber << "," 
                     << UpdatedStudent.name << "," 
                     << UpdatedStudent.department << "\n";
            cout << "Success: Student record updated!\n";

        }
        else{
            tempFile << line << "\n";
        }
    }

    fin.close();
    tempFile.close();

    //Delete the old file and rename the new one
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (!found) {
        cout << "Error: Student with Roll Number " << targetRoll << " not found.\n";
    }

    cout << "Update Students function called.\n";
}

void deleteStudent() {
    
    int targetroll;
    cout << "\n<--- Delete Student --->\n";
    cout << "Enter the Roll Number to delete: ";
    cin >> targetroll;

    ifstream fin("students.txt");
    ofstream tempfile("temp.txt");

    //checking whether the two files are opened or not
    if(!fin.is_open() || !tempfile.is_open()){
        cout << "Error: Could not open files.\n";
        return;
    }

    string line;
    bool found=false;

    while(getline(fin,line)){
        stringstream ss(line);
        string rollstr;

        getline(ss,rollstr,',');
        if(stoi(rollstr) == targetroll){
            found=true;
            //skip this line, result into not adding in temp file -> means deleted
            cout << "Success: Student record deleted!\n";

        }

        else{
            tempfile<<line<<"\n";
        }

    }
    fin.close();
    tempfile.close();

    remove("students.txt");
    rename("temp.txt","students.txt");

    if (!found) {
        cout << "Error: Student with Roll Number " << targetroll << " not found.\n";
    }

    cout << "Delete Students function called.\n";

    
}

int main() {
    int choice;
    
    // The Menu-Driven Operation
    do {
        cout << "\n=== Student Management System ===\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}