//There is a special catch block called "catch all" catch(...) that can be used to catch all types of exceptions.
#include <iostream> 
using namespace std; 
  
int main() 
{ 
    try  { 
       throw 10; 
    } 
    catch (char *excp)  { 
        cout << "Caught " << excp; 
    } 
    catch (...)  { 
        cout << "Default Exception\n"; 
    } 
    return 0; 
}

