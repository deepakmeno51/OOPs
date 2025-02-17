#include <iostream>
using namespace std;

class Metal {
public:
    string name; // Name of the metal
    string malleability; // Malleability level
    string stability; // Stability of the metal
    string rarity; // Rarity level
    double value; // Value of the metal

    void get_details();
    void display(); 
};

void Metal:: get_details() {
        cout << "Enter name of the metal: ";
        cin >> name;
        cout << "Enter malleability level: ";
        cin >> malleability;
        cout << "Enter stability level: ";
        cin >> stability;
        cout << "Enter rarity level: ";
        cin >> rarity;
        cout << "Enter value of the metal: ";
        cin >> value;
    }

 void Metal::display display() {
        cout << "The name of the metal is: " << name << endl;
        cout << "The malleability level is: " << malleability << endl;
        cout << "The stability level is: " << stability << endl;
        cout << "The rarity level is: " << rarity << endl;
        cout << "The value of the metal is: " << value << " USD" << endl;
    }   


int main() {
    Metal gold, silver, platinum;
    
    gold.get_details();
    silver.get_details();
    platinum.get_details();
    
    gold.display();
    silver.display();
    platinum.display();
    
    return 0;
}
