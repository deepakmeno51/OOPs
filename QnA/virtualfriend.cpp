#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() const { 
        cout << "Base class show()" << endl; 
    }

    friend void callShow(const Base& obj); // Friend function
};

class Derived : public Base {
public:
    void show() const override { 
        cout << "Derived class show()" << endl; 
    }
};

// Friend function that calls a virtual function
void callShow(const Base& obj) {
    obj.show(); // Calls the appropriate virtual function based on dynamic type
}

int main() {
    Base b;
    Derived d;

    callShow(b); // Calls Base::show()
    callShow(d); // Calls Derived::show() due to dynamic dispatch

    return 0;
}

