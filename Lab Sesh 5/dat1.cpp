#include <iostream>
using namespace std;

const int GLOBAL_MAX = 9; // Declared as a constant for safety

class Max {
public:
    int findMax(int x, int y) { // Clear function name
        return (x > y) ? x : y;
    }
};

int main() {
    int localMax = 4; // Clearer variable name
    Max m1;
    
    int result = m1.findMax(7, 8); // Avoid reusing "max" as a variable name
    cout << "Max of (7,8): " << result << endl;
    cout << "Local max: " << localMax << endl;
    cout << "Global max: " << GLOBAL_MAX << endl; // Accessing the global variable safely

    return 0;
}
