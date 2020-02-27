#include<iostream>
#include<vector>
#include<string>
using namespace std;

vector<int> filter(const vector<int> &vec, int val, bool (*pred)(int,int));

bool less_than(int v1,int v2)
{return v1<v2 ? true:false;}

bool greater_than(int v1,int v2)
{return v1>v2 ? true:false;}

int main()
{
	int seq[10]={1,1,2,3,5,8,13,21,34,55};
	vector<int> vec(seq,seq+10);
	int val=10;
	
	vector<int> nvec=filter(vec,val,greater_than);

	for (vector<int>::iterator iter=nvec.begin(); iter<nvec.end();iter++)
	cout<<*iter<<'\t';

	string blank;
	cin>>blank;
}