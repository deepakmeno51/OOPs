//Using sizeof operator to detect existence of VPTR 
#include <iostream>
using namespace std;
class nonvirtual{
int x;
public:
void func()
{
}
};

class withvirtual
{
int x; public:
virtual void func()
{
}
};
int main()
{
cout << sizeof( nonvirtual)<< endl;
cout << sizeof( withvirtual);
return 0;
}

