#include <iostream>
/*An essential standard library is iostreams, which facilitates reading input from files and the keyboard, 
as well as writing output to files and the display.*/
using namespace std;
class language
{
        public:
            string name;
            string script;
            string countries_that_use_this_language;
            int num_of_speakers;

            void set()
            {
                cout<<"Enter the name of the language:";
                cin>> name;
                cout<< "Enter the script of the language";
                cin>> script;
                cout<< "Enter the countries that speak this language:";
                cin>> countries_that_use_this_language ;
                cout<< "Enter the num of speakers: ";
                cin>> num_of_speakers;

            }
            void display()
            {
                cout<< " "<< name << endl;
                cout<< "uses the" << script ;
                cout<< countries_that_use_this_language <<"are the countries to speak this language" ;
                cout << "and has" << num_of_speakers << "of speakers";

            }
};

int main()
{
    language l;
    l.set();
    l.display();
}