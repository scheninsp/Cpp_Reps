#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool seq_elem(int pos, int &elem, vector<int>* (*seq_ptr)(int)); 
//bool seq_elem(int pos, int &elem, const vector<int>* (*seq_ptr)(int));  //declaration of functions
vector<int>* fibon_seq(int size);
//const vector<int>* fibon_seq(int size);

int main()
{
	int pos;
	cout <<"Please input the position.\n";
	cin >> pos;

	int elem=0;

	vector<int>* (*seq_array[])(int) =  { 
	fibon_seq};
	//const vector<int>* (*seq_array[])(int) =  { //an array of pointers to functions
	//	fibon_seq};

	enum ns_type {
	ns_fibon};

	vector<int>* (*seq_ptr)(int)=0; 
	//const vector<int>* (*seq_ptr)(int)=0;  //a pointer to function

	seq_ptr=seq_array[ns_fibon];

	bool result;
	result = seq_elem(pos,elem,seq_ptr);

	if (!result)
		cout<<"Cannot return the answer.\n";
	else
		cout<<"The no."<<pos<< " element in sequence is "<<elem<<".\n";

	string blank;
	cin>>blank;

	return 0;
}

