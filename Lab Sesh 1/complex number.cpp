#include <iostream>
using namespace std;

class Complex {
private:
    float re; // Real part
    float im; // Imaginary part

public:
    // Default constructor
    Complex() : re(0), im(0) {}

    // Function to input a complex number
    void set() {
        cout << "Enter the real part: ";
        cin >> re;
        cout << "Enter the imaginary part: ";
        cin >> im;
    }

    // Function to add two complex numbers
    Complex add(Complex c) {
        Complex result;
        result.re = re + c.re;
        result.im = im + c.im;
        return result;
    }

    // Function to display a complex number
    void display() {
        if (im > 0)
            cout << re << " + " << im << "i" << endl;
        else if (im == 0)
            cout << re << endl;
        else
            cout << re << " - " << -im << "i" << endl;
    }
};

int main() {
    int n;
    cout << "How many complex numbers do you want to add? ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid input. Exiting program." << endl;
        return 1;
    }

    Complex sum, temp;
    
    for (int i = 0; i < n; ++i) {
        cout << "Complex number " << i + 1 << ":-" << endl;
        temp.set();
        sum = sum.add(temp);
    }

    cout << "The sum of the given complex numbers is: ";
    sum.display();

    return 0;
}
