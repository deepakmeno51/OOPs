// C++ program to explain  
// Single inheritance 

#include <iostream>  // Including the input-output stream library
using namespace std; // Using the standard namespace
  
// Base class 
class Vehicle1 { 
  public: 
    // Constructor of the base class
    Vehicle1() 
    { 
      cout << "This is a Vehicle" << endl; // Display message when an object is created
    } 
}; 
  
// Subclass (derived class) inheriting from the base class
class Car: private Vehicle1 { //vehicle functions becomes public memeber for car class
  // No additional members or methods in Car class
  // protected membr func/var are similar to private mem func/var
}; 
  
// Main function 
int main() 
{    
    // Creating an object of the derived class Car
    // This automatically invokes the constructor of the base class Vehicle
    Car obj; 
  
    return 0; // Indicating successful program termination
}
