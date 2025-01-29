#include <iostream>
using namespace std;

class Planet {
public:
    string name; // Name of the planet
    double mass; // Mass of the planet
    string inhabitability; // Whether it is habitable or not
    int order_in_milkyway; // Order from the sun
    double surface_temperature; // Surface temperature in Celsius
    double distance_from_sun; // Distance from the sun in million km

    void get_details() {
        cout << "Enter name of the planet: ";
        cin >> name;
        cout << "Enter mass of the planet (in Earth masses): ";
        cin >> mass;
        cout << "Enter inhabitability (Habitable/Non-habitable): ";
        cin >> inhabitability;
        cout << "Enter order in the Milky Way: ";
        cin >> order_in_milkyway;
        cout << "Enter surface temperature (in Celsius): ";
        cin >> surface_temperature;
        cout << "Enter distance from the Sun (in million km): ";
        cin >> distance_from_sun;
    }

    void display() {
        cout << "The name of the planet is: " << name << endl;
        cout << "The mass of the planet is: " << mass << " Earth masses" << endl;
        cout << "The inhabitability status is: " << inhabitability << endl;
        cout << "The order in the Milky Way is: " << order_in_milkyway << endl;
        cout << "The surface temperature is: " << surface_temperature << "°C" << endl;
        cout << "The distance from the Sun is: " << distance_from_sun << " million km" << endl;
    }

    void temperature_and_distance_from_sun() {
        cout << name << " is " << distance_from_sun << " million km away from the Sun and has a surface temperature of " << surface_temperature << "°C." << endl;
    }
};

int main() {
    Planet earth, jupiter, mars;
    
    earth.get_details();
    jupiter.get_details();
    mars.get_details();
    
    earth.display();
    jupiter.display();
    mars.display();
    
    earth.temperature_and_distance_from_sun();
    jupiter.temperature_and_distance_from_sun();
    mars.temperature_and_distance_from_sun();

    return 0;
}
