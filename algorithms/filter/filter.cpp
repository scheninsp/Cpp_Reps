//practice generic function
#include<vector>
using namespace std;

vector<int> filter(const vector<int> &vec, int val, bool (*pred)(int,int))
{
	vector<int> nvec;
	for (int ix=1;ix<vec.size();ix++){
		if ((*pred)(vec[ix],val))
			nvec.push_back(vec[ix]);
	}
	return nvec;
}
