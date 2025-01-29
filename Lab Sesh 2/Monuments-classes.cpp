#include <iostream>
/*An essential standard library is iostreams, which facilitates reading input from files and the keyboard, 
as well as writing output to files and the display.*/
using namespace std;
class Monument //class definition does not occupy memory because it is a logical construct
{
    public:
            string name;
            string place;

            void set()  
            {
            cout <<"Enter the name of the monument:" ;
            cin>> name;
            cout<<"Enter the place of the monument" ;
            cin>> place;
            }

            void display()
            {
                cout<<" "<< name << endl ; 
                cout<< "It is located in"<< place ;
            }

};

int main()
{
        Monument l;
        l.set();
        l.display();
}
