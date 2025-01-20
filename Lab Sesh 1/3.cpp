#include<iostream>
/*An essential standard library is iostreams, which facilitates reading input from files and the keyboard, 
as well as writing output to files and the display.*/

using namespace std; //All of the Standard C++ libraries are wrapped in a single namespace, which is std (for “standard”).
int main()
{
	int i,j,count;
	count = 0;
	i = 0;
	for (j=-3; j<=3; j++)
	{
		if((j >= 0) && i++)
		count = count +j;
	}
	count = count + i;
	cout<<count<<endl; /*The operator cout is an object Belongs to output stream class Used to perform write operations on the output devices e.g. screen, disk etc.*/
	return 0;
}