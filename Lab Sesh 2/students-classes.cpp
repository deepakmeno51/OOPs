#include <iostream>
using namespace std;

class Student {
public:
    string name; // Name of the student
    int semester; // Current semester
    int no_of_subjects; // Number of subjects
    double total_marks_secured; // Total marks secured

    void get_details() {
        cout << "Enter name of the student: ";
        cin >> name;
        cout << "Enter semester: ";
        cin >> semester;
        cout << "Enter number of subjects: ";
        cin >> no_of_subjects;
        cout << "Enter total marks secured: ";
        cin >> total_marks_secured;
    }

    void display() {
        cout << "The name of the student is: " << name << endl;
        cout << "The semester is: " << semester << endl;
        cout << "The number of subjects is: " << no_of_subjects << endl;
        cout << "The total marks secured is: " << total_marks_secured << endl;
    }

    void average_marks_secured() {
        double average = total_marks_secured / no_of_subjects;
        cout << name << " has an average mark of " << average << " per subject." << endl;
    }
};

int main() {
    Student student1, student2, student3;
    
    student1.get_details();
    student2.get_details();
    student3.get_details();
    
    student1.display();
    student2.display();
    student3.display();
    
    student1.average_marks_secured();
    student2.average_marks_secured();
    student3.average_marks_secured();
    
    return 0;
}
