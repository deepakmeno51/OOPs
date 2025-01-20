#include<iostream>
/*An essential standard library is iostreams, which facilitates reading input from files and the keyboard, 
as well as writing output to files and the display.*/

using namespace std; //All of the Standard C++ libraries are wrapped in a single namespace, which is std (for “standard”).
int main(){
	float sum = 0.0, j = 1.0, i = 2.0;
	while(i/j > 0.0625){
		j = j + j;
		sum = sum + i/j;
		cout<<sum<<endl; /*The operator cout is an object Belongs to output stream class Used to perform write operations on the output devices e.g. screen, disk etc.*/
	}
	return 0;
}