#include <iostream>
using namespace std;

class Complex {
    int a , b;
    public:
        Complex(){
            a = 3;
            b = 4;
        }
        void display(){
            cout<<a<< " + " <<b<<"i" ;

        }
}; 

int main () {
    Complex x1;
    x1.display();
    return 0;
}
