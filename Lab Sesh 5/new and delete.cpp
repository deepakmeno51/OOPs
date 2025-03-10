#include <iostream>
using namespace std;

int main() {
int* pointer1 = new int(700);
int* pointer2 = new int(300);
cout << "Sum: " << (*pointer1 + *pointer2) << endl;
cout << "Difference: " << (*pointer1 - *pointer2) << endl;
cout << "Product: " << (*pointer1 * *pointer2) << endl;
cout << "Quotient: " << (*pointer1 / *pointer2) << endl;
delete pointer1;
delete pointer2;
return 0;
}