#include <iostream>
using namespace std;

class Food {
public:
    string name; // Name of the food
    string color; // Color of the food
    string taste; // Taste of the food
    double cost; // Cost of the food

    void get_details() {
        cout << "Enter name of the food: ";
        cin >> name;
        cout << "Enter color of the food: ";
        cin >> color;
        cout << "Enter taste of the food: ";
        cin >> taste;
        cout << "Enter cost of the food: ";
        cin >> cost;
    }

    void display() {
        cout << "The name of the food is: " << name << endl;
        cout << "The color of the food is: " << color << endl;
        cout << "The taste of the food is: " << taste << endl;
        cout << "The cost of the food is: " << cost << " USD" << endl;
    }
};

int main() {
    Food pizza, sushi, burger;
    
    pizza.get_details();
    sushi.get_details();
    burger.get_details();
    
    pizza.display();
    sushi.display();
    burger.display();
    
    return 0;
}
