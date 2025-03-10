#include<iostream>
using namespace std;
class cc
{
private:
int x, y; // data members
public:
cc(int x1, int y1)
{
x = x1;
y = y1;
}
// Copy constructor
cc (const cc &sam)// copy constructor,sam is a reference object of class cc having defined address that canot be changes
{
x = sam.x;
y = sam.y;
}
~cc()
{
cout<<"destructor called"<<endl;
}

void display()
{
cout<<x<<" "<<y<<endl;
}
};
int main()
{
cc obj1(10,15); // Normal constructor
cout<<&obj1<<endl;
cout<<"Normal constructor : "<< endl;
obj1.display();
cc obj2 = obj1; // Copy constructor
cout<<&obj2<<endl;
cout<<"Copy constructor : "<<endl;
obj2.display();
return 0;
}
