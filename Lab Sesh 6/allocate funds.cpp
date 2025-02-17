#include <iostream>
using namespace std;

class Company {
private:
    float initialCapital;
    float allocatedA, allocatedB, allocatedC;

public:
    // Constructor to initialize capital
    Company(float capital) : initialCapital(capital), allocatedA(0), allocatedB(0), allocatedC(0) {}

    // Function to allocate funds dynamically
    void allocateFunds(float a, float b, float c) {
        if (a + b + c > initialCapital) {
            cout << "Error: Insufficient capital to allocate funds!" << endl;
            return;
        }
        allocatedA = a;
        allocatedB = b;
        allocatedC = c;
    }

    float calculateRemainingCapital() {
        return initialCapital - (allocatedA + allocatedB + allocatedC);
    }

    // Function to display allocated funds for each sub-branch
    void displayAllocatedFunds() {
        cout << "DESCRIPTION: " << endl;
        cout << "--------------------------------------------------------------------" << endl;
        cout << "Funds allocated to Sub-branch A: Rs " << allocatedA << " Lakhs" << endl;
        cout << "Funds allocated to Sub-branch B: Rs " << allocatedB << " Lakhs" << endl;
        cout << "Funds allocated to Sub-branch C: Rs " << allocatedC << " Lakhs" << endl;
        cout << "--------------------------------------------------------------------" << endl;
    }

    // Function to display remaining capital
    void displayRemainingCapital() {
        cout << "Remaining capital with Company X: Rs " << calculateRemainingCapital() << " Lakhs" << endl;
    }
};

int main() {
    Company comp(50.0); // Initialize company with 50 Lakhs capital

    // Allocate funds dynamically
    comp.allocateFunds(15.0, 14.0, 9.0);

    // Display allocated funds and remaining capital
    comp.displayAllocatedFunds();
    comp.displayRemainingCapital();

    return 0;
}
