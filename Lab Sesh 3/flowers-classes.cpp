#include <iostream>
using namespace std;

class Flower {
public:
    string name; // Name of the flower
    string colour; // Colour of the flower
    int number_of_petals; // Number of petals
    string rarity; // Rarity level (common, rare, etc.)
    string region_of_growth; // Where the flower grows
    string climate_of_growth; // Climate where it thrives

    void get_details() {
        cout << "Enter name of the flower: ";
        cin >> name;
        cout << "Enter colour of the flower: ";
        cin >> colour;
        cout << "Enter number of petals: ";
        cin >> number_of_petals;
        cout << "Enter rarity of the flower: ";
        cin >> rarity;
        cout << "Enter region of growth: ";
        cin >> region_of_growth;
        cout << "Enter climate of growth: ";
        cin >> climate_of_growth;
    }

    void display() {
        cout << "The name of the flower is: " << name << endl;
        cout << "The colour of the flower is: " << colour << endl;
        cout << "The number of petals is: " << number_of_petals << endl;
        cout << "The rarity level is: " << rarity << endl;
        cout << "The region of growth is: " << region_of_growth << endl;
        cout << "The climate of growth is: " << climate_of_growth << endl;
    }

    void number_of_petals_on_climate() {
        cout << name << " grows in " << climate_of_growth << " climate and has " << number_of_petals << " petals." << endl;
    }
};

int main() {
    Flower rose, lotus, tulip;
    
    rose.get_details();
    lotus.get_details();
    tulip.get_details();
    
    rose.display();
    lotus.display();
    tulip.display();
    
    rose.number_of_petals_on_climate();
    lotus.number_of_petals_on_climate();
    tulip.number_of_petals_on_climate();

    return 0;
}
