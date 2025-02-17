#include <iostream>
using namespace std;

int main()
{
    int a =1, b =2, c =3;
    int &z = a; // variable z becomes alias of a 
    cout << "a=" << a << "b=" << b << "c=" << c << "z=" << z << endl;
    z = b;     // changes value of a to the value of b 
    cout << "a=" << a << "b=" << b << "c=" << c << "z=" << z << endl;
    z = c; // changes value of a to the value of c
    cout << "a=" << a << "b=" << b << "c=" << c << "z=" << z << endl;
    cout << "&a" << &a << "&b=" << &b << "&c=" << &c << "&z=" << &z << endl;
}
