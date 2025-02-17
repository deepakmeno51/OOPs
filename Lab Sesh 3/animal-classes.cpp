#include <iostream>
using namespace std;

class Animal {
public:
    string name; // Name of the animal
    string habitat; // Habitat type
    string type; // Type of animal (mammal, bird, etc.)
    string heterotrophy; // How the animal gains food (carnivore, herbivore, omnivore)
    string country; // Country where it is found
    int population; // Estimated population

    void get_details();
    void display();
    void type_based_on_habitat();

    
};

void Animal:: get_details() {
        cout << "Enter name of the animal: ";
        cin >> name;
        cout << "Enter habitat of the animal: ";
        cin >> habitat;
        cout << "Enter type of the animal: ";
        cin >> type;
        cout << "Enter heterotrophy (carnivore/herbivore/omnivore): ";
        cin >> heterotrophy;
        cout << "Enter country where it is found: ";
        cin >> country;
        cout << "Enter estimated population: ";
        cin >> population;
    }

void Animal:: display() {
        cout << "The name of the animal is: " << name << endl;
        cout << "The habitat of the animal is: " << habitat << endl;
        cout << "The type of the animal is: " << type << endl;
        cout << "The heterotrophy of the animal is: " << heterotrophy << endl;
        cout << "The country where it is found: " << country << endl;
        cout << "The estimated population is: " << population << endl;
    }

 void Animal:: type_based_on_habitat() {
        cout << name << " is a " << type << " and typically found in " << habitat << "." << endl;
    }

int main() {
    Animal kangaroo, elephant, penguin;
    
    kangaroo.get_details();
    elephant.get_details();
    penguin.get_details();
    
    kangaroo.display();
    elephant.display();
    penguin.display();
    
    kangaroo.type_based_on_habitat();
    elephant.type_based_on_habitat();
    penguin.type_based_on_habitat();

    return 0;
}
