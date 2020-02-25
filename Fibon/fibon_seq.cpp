#include <iostream>
#include <string>
#include <vector>

using namespace std;

inline bool is_size_ok(int size)   //This must put before the function who calls it.
{
	const int max_size=1024;
	if(size<=0||size>max_size){
		std::cerr << "requested size is not supported. "
			<<size <<" can't fullfill request.\n";
		return false;
	}
	return true;
}

vector<int>* fibon_seq(int size)
//const vector<int>* fibon_seq(int si`ze)  //const is for locate the address elems
{
	const int max_size = 1024;
	static vector<int> elems;

	if(!is_size_ok(size))
	return 0;

	for (int ix = elems.size();ix<size; ++ix){
		if (ix==0||ix==1)
			elems.push_back(1);
		else 
		{//cout<<elems[ix-1]<<'\t'<<elems[ix-2]; //for test
			elems.push_back(elems[ix-1]+elems[ix-2]);}
	}
	return &elems;
}
