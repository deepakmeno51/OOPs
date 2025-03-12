#include<iostream>

using namespace std; 

class Complex {

private:

    int real=1, imag=3;

public:

// Complex(){

 //           real=0;

 //           imag=0;

// }

    Complex(int r=0, int i=0)  {real = r;   imag = i;}

         // This is automatically called when '+' is used with

    // between two Complex objects

    Complex operator - (Complex obj) { // operator keyword followed by tkhe toperator you want to overload
                                        // operator functions should have operator arguments
         Complex res;

         res.real = real + obj.real;

         res.imag = imag + obj.imag;

         return res;

    }

    void print() { cout << real << " + i" << imag << endl; }

};

 int main()

{

    Complex c1(10, 5), c2(2, 4);

    Complex c3 = c1 + c2; // An example call to "operator+"

    c3.print();

}