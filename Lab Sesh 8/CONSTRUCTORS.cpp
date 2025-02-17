#include <iostream>
using namespace std;
class X {
    int i;
    string Name;
	public:
	  X(){  //Constructor in C++ is a special method that is invoked automatically at the time an object of a class is created. It is used to initialize the data members of new objects generally
	      i=100;
	      Name="Sai";
	  }
	  	void display(){
	
	    cout<<"Swami's age is "<<i<<endl;
	  }
	};
	
int main() {
  X x1; 
  //cout<<x1.i<<endl;
  //cout<<x1.Name<<endl;
  x1.display();
  return 0;   
}
