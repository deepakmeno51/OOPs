//Implicit type conversion does not happen for primitive types.
#include <iostream> 
using namespace std; 
  
int main() 
{ 
int a;
    try  { 
       throw a; 
    } 
    catch (char x)  { 
        cout << "Caught "; // terminates code before catching it
    } 
    return 0; 
}

