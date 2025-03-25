#include <iostream>
using namespace std;

class Demo {
public:
    void show() {  // Non-const member function
        cout << "Non-const show()" << endl;
    }

    void display() const {  // Const member function
        cout << "Const display()" << endl;
    }
};

int main() {
    const Demo obj;  // Creating a constant object

    // obj.show();  // ? ERROR: Cannot call a non-const function on a const object
    obj.display();  // ? OK: Can call a const function

    return 0;
}

