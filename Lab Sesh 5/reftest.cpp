#include <iostream>
using namespace std;

int main()
{
    int n = 100;
    int *p = &n;
    int &m = *p; // m is bound to n
    cout << " n= " << n << "m = " << m << "p= " << p << endl;
    int k = 5;
    p = &k ; // pointer value has changed
    k = 200; 
    // is there change in m value?
    cout << " n= " << n << "m = " << m << "p= " << p << endl;
}
