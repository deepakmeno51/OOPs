// copy constructor
//one object intailize the other
//passing objects as parameters,intailization does happen
//return of objects from member function
// Assignment operator

#include <iostream>

using namespace std;

class A
{
	 public:
       	A() { 
    	  cout << "Constructor" << endl; 
      	}
       	~A() { 
    	   cout << "Destructor" << endl; 
        }
	void show()
	{
	cout<<"i am copied"<<endl;
	}
};

int main()
{
	A a1;// Constructor will be called a1,default constrcutor
	cout<<&a1<<endl;
	A a2=a1;//a2 is intailized by a1.bit-wise copying,share the same memory,assignment statement
	cout<<&a2<<endl;	
	a2.show();//destrcutor of a1 or a2,
	return 0;
}
