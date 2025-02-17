// C++ program to implement  
// Multilevel Inheritance 

#include <iostream>  // Including input-output stream library
using namespace std; // Using standard namespace
  
// Base class 
class Vehicle  
{ 
  protected: // Protected access specifier allows derived classes to access members
    Vehicle()  // Constructor of the base class
    { 
      cout << "This is a Vehicle" << endl; // Message displayed when an object is created
    } 
}; 

// Intermediate derived class inheriting from Vehicle 
class fourWheeler: protected Vehicle 
{  
  public: 
    fourWheeler()  // Constructor of fourWheeler class
    { 
      cout << "Objects with 4 wheels are vehicles" << endl; 
    } 
}; 

// Subclass (final derived class) inheriting from fourWheeler
class Car: protected fourWheeler
{  
   public: 
     Car()  // Constructor of Car class
     { 
       cout << "Car has 4 Wheels" << endl; 
     } 
}; 
  
// Main function 
int main() 
{    
    // Creating an object of the Car class
    // This will invoke the constructors of all base classes in the order of inheritance
    Car obj; 
  
    return 0; // Indicating successful program termination
}


