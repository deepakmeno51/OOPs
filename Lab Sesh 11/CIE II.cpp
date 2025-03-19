#include <iostream>
using namespace std;

class Patient {
public:
    string p, d;

    // Constructor to take input
    Patient() {
        cout << "Please enter patient's name: ";
        cin >> p;
        cout << "Please enter the name of the disease: ";
        cin >> d;
    }

    void display() {
        cout << "Patient Name: " << p << endl;
        cout << "Disease: " << d << endl;
    }
};

class Out_P {
public:
    float O;

    // Constructor for Out_P
    Out_P() {
        cout << "Input OPD Charges: ";
        cin >> O;
    }

    void display() {
        cout << "OPD Charges: " << O << endl;
    }
};

class In_P {
public:
    float I;

    // Constructor for In_P
    In_P() {
        cout << "Input the total room rent: ";
        cin >> I;
    }

    void display() {
        cout << "Total Room Rent: " << I << endl;
    }
};

// Function to display patient details
void putdata(Patient &p, Out_P &op, In_P &ip) {
    p.display();
    op.display();
    ip.display();
}

int main() {
    Patient patient;
    Out_P out_patient;
    In_P in_patient;

    cout << "\nPatient Details:\n";
    putdata(patient, out_patient, in_patient);

    return 0;
}
        