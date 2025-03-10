#include<iostream>

using namespace std;

class A{

	public:

	virtual void display() = 0;

			};

class B:public A{

	public:

	void display(){

		cout<<"I am in Derived Class";

	}

};

int main(){

	A a1;

	B b1;

	b1.display();

	return 0;

}