
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    float marks;

    void input() {
        cout << "Enter roll number: ";
        cin >> rollNo;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter student name: ";
        getline(cin, name);

        cout << "Enter marks (0-100): ";
        cin >> marks;
    }

    void display() const {
        cout << "Roll Number: " << rollNo << '\n';
        cout << "Name: " << name << '\n';
        cout << "Marks: " << marks << "/100\n";
        cout << "-------------------------\n";
    }
};

bool rollExists(int roll) {
    ifstream file("students.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        int savedRoll;
        if (ss >> savedRoll && savedRoll == roll) {
            return true;
        }
    }
    return false;
}

void addStudent() {
    Student s;
    s.input();

    if (s.rollNo <= 0 || s.marks < 0 || s.marks > 100) {
        cout << "Invalid roll number or marks.\n";
        return;
    }

    if (rollExists(s.rollNo)) {
        cout << "This roll number already exists.\n";
        return;
    }

    ofstream file("students.txt", ios::app);
    file << s.rollNo << '\n'
         << s.name << '\n'
         << s.marks << '\n';

    cout << "Student record saved successfully.\n";
}

void viewStudents() {
    ifstream file("students.txt");

    if (!file) {
        cout << "No student records found yet.\n";
        return;
    }

    Student s;
    while (file >> s.rollNo) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, s.name);

        if (!(file >> s.marks)) {
            cout << "Record file is incomplete.\n";
            return;
        }
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        s.display();
    }
}

void searchStudent() {
    int target;
    cout << "Enter roll number to search: ";
    cin >> target;

    ifstream file("students.txt");
    Student s;

    while (file >> s.rollNo) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, s.name);

        if (!(file >> s.marks)) {
            break;
        }
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        if (s.rollNo == target) {
            s.display();
            return;
        }
    }

    cout << "Student not found.\n";
}

int main() {
    int choice;

    do {
        cout << "\n=== Student Management System ===\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";

        if (!(cin >> choice)) {
            cout << "Please enter a valid menu number.\n";
            return 1;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
