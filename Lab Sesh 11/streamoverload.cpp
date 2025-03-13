#include <iostream>
using namespace std;

class Complex {
private:
    double real, imag;
public:
    Complex() : real(0), imag(0) {}
    Complex(double r, double i) : real(r), imag(i) {}
    
    // Overload >> operator for input
    friend istream& operator>>(istream& sun, Complex& c) {
        cout << "Enter real and imaginary parts: ";
        sun >> c.real >> c.imag;
        return sun;
    }
    
    // Overload << operator for output
    friend ostream& operator<<(ostream& moon, const Complex& c) {
        moon << c.real << " + " << c.imag << "i";
        return moon;
    }
    
    // Overload + operator for addition
    Complex operator+(const Complex& c) const {
        return Complex(real + c.real, imag + c.imag);
    }
};

int main() {
    Complex c1, c2, sum;
    
    cout << "Enter first complex number:" << endl;
    cin >> c1;
    cout << "Enter second complex number:" << endl;
    cin >> c2;
    
    sum = c1 + c2;
    
    cout << "Sum: " << sum << endl;
    
    return 0;
}

//invoking the stream required for that particular operator

