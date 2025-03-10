#include<iostream>  // Include the input/output stream library for console operations

using namespace std;  // Use the standard namespace to avoid prefixing std:: before cout

class A {  // Define base class A
    public:  // Public access specifier - members below are accessible from outside the class
        
        // Pure virtual function declaration
        // '= 0' makes it pure virtual, forcing derived classes to implement it
        // Makes class A an abstract class that cannot be instantiated directly
        virtual void display() = 0; 
};

class B : public A {  // Define class B that inherits publicly from class A
    public:  // Public access specifier
        
        // Implementation of the pure virtual function from base class A
        // This is mandatory as B inherits from A
        void display() {
            cout << "I am in Derived Class";  // Outputs message to console
        }
};

int main() {  // Main function - program entry point
    
    // A a1;  // This line would cause a compilation error
    // Cannot create object of abstract class A due to pure virtual function
    
    B b1;  // Create object of derived class B
    
    b1.display();  // Call display() function on b1 object
                  // Will print "I am in Derived Class" to console
    
    return 0;  // Return 0 to indicate successful program completion
}