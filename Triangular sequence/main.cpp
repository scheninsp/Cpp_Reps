#include<iostream>
#include"Triangular.h"
using namespace std;

int main()
{
	//judge whether an element exist in this type of sequence
	/*char ch;
	bool more=true;

	while(more){
	cout<<"Enter value: ";
	int ival;
	cin >> ival;

	bool is_elem = Triangular::is_elem(ival);

	cout<<ival
		<<(is_elem ? " is " : " is not ")
		<<"an element in the Fibonacci series.\n"
		<<"Another value? (y/n)";

	cin >> ch;
		if(ch=='n'||ch=='N')
			more =false;
	}*/

	//traverse the sequence vector
	Triangular tri(15,1);
	//cout<<tri._elems.back();  //for test

	Triangular::iterator it = tri.begin();
	Triangular::iterator end_it = tri.end();

	cout<<"Fibonacci series of " << tri.length() << " elements \n";
	//cout<< tri <<endl;
	while(it != end_it)
	{
		cout<<*it<<' ';
		++it;
	}
	cout<< endl; 

	int blank;
	cin >> blank;
}