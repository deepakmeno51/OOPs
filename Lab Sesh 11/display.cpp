#include <iostream>
using namespace std; 

class a {
    public:
        void displayone() {  
            cout << "I belong to parent class" << endl; 
        }
};

class b: public a {
    public:
        void displayone() {  // this member function overrides displayone in the parent class
            cout << "I belong to the child class" << endl; 
        }
};

int main() {
    b obj_b;  
    obj_b.displayone();
    obj_b.displayone();
    return 0;
}


//class a has a function which is declared but not defined hence a is an abstract class
