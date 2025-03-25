//In C++, constructors cannot be virtual because:
//Virtual functions rely on the vtable, which is set up after the constructor is executed.
//Constructors are responsible for creating objects.
//Before the object exists, there is no vtable to determine the correct constructor to call.
#include <iostream>
using namespace std;

class Base {
public:
    virtual Base() { // ? ERROR: Constructors cannot be virtual
        cout << "Base Constructor" << endl;
    }
};

int main() {
    Base obj;
    return 0;
}

