#include <iostream>
/*An essential standard library is iostreams, which facilitates reading input from files and the keyboard, 
as well as writing output to files and the display.*/
using namespace std;
class car
{
    public: 
        string country_of_origin; // member variables
        string name ; //member variable
        string engine; //member variables
        int price, mileage, horsepower, torque, weight, fuel_used ; //member variables

        void get_details() //member functions
        {
            cout<< "Enter name of car";
            cin>> name;
            cout<< "Enter name of country_of_origin ";
            cin>> country_of_origin;
            cout<< "Enter engine  of car ";
            cin>> engine;
            cout<< "Enter price of car";
            cin>> price;
            cout<< "Enter mileage of car";
            cin>> mileage;
            cout<< "Enter horsepower of car";
            cin>>horsepower ;
            cout<< "Enter torque of car";
            cin>> torque;
            cout<< "Enter weight of car";
            cin>> weight;
            cout<< "Enter fuel_used of car";
            cin>> fuel_used;
        }
        void display()
        {
            cout<<"The name of the car is: "<<name<<endl;
            cout<<"The country_of_origin of the car is: "<<country_of_origin<<endl;
            cout<<"The engine of the car is: "<<engine<<endl;
            cout<<"The price of the car is: "<<price<<endl;
            cout<<"The mileage of the car is: "<<mileage<<endl;
            cout<<"The horsepower of the car is: "<<horsepower<<endl;
            cout<<"The torque of the car is: "<<torque<<endl;
            cout<<"The weight of the car is: "<<weight<<endl;
            cout<<"The fuel_used of the car is: "<<fuel_used<<endl;

        }

        int avg_fuel_consumption (int mileage, int fuel_used)
        {
            fuel_used / mileage * 100 = avg_fuel_consumption;
        }

        
           
};

int main() {
    car avg_fuel_consumption , country_of_origin , price; //object creation
    avg_fuel_consumption.get_details(); 
    country_of_origin.get_details();
    price.get_details();

    avg_fuel_consumption.display(); 
    country_of_origin.display();
    price.display();

    return 0;
}

