#include<iostream>
/*An essential standard library is iostreams, which facilitates reading input from files and the keyboard, 
as well as writing output to files and the display.*/
using namespace std;//All of the Standard C++ libraries are wrapped in a single namespace, which is std (for “standard”).
int foo(int x, int y, int q){
	if ((x <= 0) && (y <= 0))
	return q;
	if(x<=0)
	return foo(x, y-q, q);
	if(y <= 0)
	return foo(x-q, y, q);
	return foo(x, y-q, q) + foo(x-q, y, q);
}

int main()
{
	int r = foo(15, 15, 10);
	cout<<r; /*The operator cout is an object Belongs to output stream class Used to perform write operations on the output devices e.g. screen, disk etc.*/
	return 0;	
}