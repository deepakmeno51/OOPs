#include <iostream>
using namespace std;

class Company {
private:
    float initialCapital;

public:
    Company(float capital) : initialCapital(capital) {}
    
    bool allocateFunds(string branchName, float amount, float &allocatedFunds) {
        if (amount > initialCapital) {
            cout << "Error: Insufficient capital for " << branchName << "!\n";
            allocatedFunds = 0;
            return false;
        }
        allocatedFunds = amount;
        initialCapital -= amount;
        return true;
    }
    
    void displayRemainingCapital() {
        cout << "Remaining capital with the Company is: Rs " << initialCapital << " Lakhs\n";
    }
};

class Branch {
public:
    string name;
    float allocatedFunds;

    Branch(string branchName) : name(branchName), allocatedFunds(0) {}
    
    void displayAllocatedFunds() {
        cout << "Funds allocated to " << name << ": Rs " << allocatedFunds << " Lakhs\n";
    }
};

int main() {
    Company company(50.0);
    Branch branchA("Japan"), branchB("United States"), branchC("India");

    // Allocating funds
    company.allocateFunds(branchA.name, 15.0, branchA.allocatedFunds);
    company.allocateFunds(branchB.name, 14.0, branchB.allocatedFunds);
    company.allocateFunds(branchC.name, 9.0, branchC.allocatedFunds);

    // Displaying allocated funds
    cout << "\nDESCRIPTION:\n";
    cout << "-------------------------------------------------------------\n";
    branchA.displayAllocatedFunds();
    branchB.displayAllocatedFunds();
    branchC.displayAllocatedFunds();
    cout << "-------------------------------------------------------------\n";
    
    // Displaying remaining capital
    company.displayRemainingCapital();
    
    return 0;
}
