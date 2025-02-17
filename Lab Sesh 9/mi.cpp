// C++ program to explain  
// multiple inheritance 

#include <iostream>  // Including input-output stream library
using namespace std; // Using standard namespace
  
// First base class 
class Vehicle { 
  public: 
    void showVehicle()  // Normal function instead of constructor
    { 
      cout << "This is a Vehicle" << endl; 
    } 
}; 
  
// Second base class 
class FourWheeler { 
  public: 
    void showFourWheeler()  // Normal function instead of constructor
    { 
      cout << "This is a 4-wheeler Vehicle" << endl; 
    } 
}; 
  
// Subclass derived from two base classes 
class Car: public Vehicle, public FourWheeler { 
  public:
    void showCar()
    {
        cout << "This is a Car" << endl;
    }
}; 
  
// Main function 
int main() 
{    
    // Creating an object of the derived class
    Car obj; 
  
    // Calling functions from base classes
    obj.showVehicle();       // Calling function from Vehicle class
    obj.showFourWheeler();   // Calling function from FourWheeler class
    obj.showCar();           // Calling function from Car class
  
    return 0; // Indicating successful program termination
}
