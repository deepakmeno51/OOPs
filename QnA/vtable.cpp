//The address of virtual functions in Vtable
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base::show()" << endl; }
    virtual void display() { cout << "Base::display()" << endl; }
};

class Derived : public Base {
public:
    void show() override { cout << "Derived::show()" << endl; }
    void display() override { cout << "Derived::display()" << endl; }
};

int main() {
    Derived d;  // Create an object of Derived
    Base* ptr = &d;  // Pointer to Base pointing to Derived

    // Get the address of vtable
    void** vtablePtr = *(void***)&d;  // Access vptr inside object
//Right-hand side (*(void***)&d)
    //&d :represents Address of the object d.
   //(void***)&d :Treats the object’s address as a pointer to a pointer.
   //*(void***)&d:Dereferences that pointer, giving us the vtable address.

//Left-hand side (void** vtablePtr)

   //vtablePtr is a pointer to a pointer (void**).
   //It stores the address of the vtable, which contains function pointers.

//OVERALL
    //vptr is the first hidden member inside d.
	//*(void***)&d extracts the vptr.
    //void** vtablePtr stores the extracted vtable address.

    cout << "VTable Address: " << vtablePtr << endl;
    cout << "Function Pointer for show(): " << vtablePtr[0] << endl;
    cout << "Function Pointer for display(): " << vtablePtr[1] << endl;

    return 0;
}

