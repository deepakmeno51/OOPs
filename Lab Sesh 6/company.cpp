#include <iostream>
using namespace std;

class CompanyX {
private:
    static int Capital; // Shared among all objects
    int requiredAmount;

public:
    void requireFunds(int amount) {
        requiredAmount = amount;
    }

    bool allocateFunds() {
        if (requiredAmount > Capital) {
            cout << "Error: Insufficient funds to allocate Rs " << requiredAmount << " Lakhs!" << endl;
            return false;
        }
        Capital -= requiredAmount;
        return true;
    }

    static void displayRemainingCapital() {
        cout << "Remaining Capital: Rs " << Capital << " Lakhs" << endl;
    }
};

// Initializing static member
int CompanyX::Capital = 50;

int main() {
    CompanyX A, B, C;

    A.requireFunds(15);
    if (A.allocateFunds()) CompanyX::displayRemainingCapital();

    B.requireFunds(10);
    if (B.allocateFunds()) CompanyX::displayRemainingCapital();

    C.requireFunds(9);
    if (C.allocateFunds()) CompanyX::displayRemainingCapital();

    return 0;
}
