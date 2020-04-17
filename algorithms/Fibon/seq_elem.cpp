#include <vector>

using namespace std;

bool seq_elem(int pos, int &elem, vector<int>* (*seq_ptr)(int))
//bool seq_elem(int pos, int &elem, const vector<int>* (*seq_ptr)(int))
{
	vector<int> *pseq = seq_ptr(pos);
	//const vector<int> *pseq = seq_ptr(pos);

	if(! pseq)
	{elem=0; return false;}
	else
	{elem = (*pseq)[pos-1];
	return true;}
}
