#include <iostream>
using namespace std;

class User {
public:
    int x;  // Added member variable since it was used in input()
    void input() {
        cout << "Enter x: ";
        cin >> x;
    }
};

int main() {
    int x = -1;      // Initial value
    User user;       // Creating User object
    
    cout << "Before try \n";
    try {
        cout << "Inside try \n";
        if (x > 0) {  // Condition to throw exception
            throw x;
            cout << "After throw (Never executed) \n";  // This won't execute if exception is thrown
        }
    }
    catch (int x) {  // Catching integer exception
        cout << "Exception Caught \n";
    }
    
    cout << "After catch (Will be executed) \n";
    return 0;
}