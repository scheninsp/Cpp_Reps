#include<vector>
#include<algorithm>
#include<iostream>
#include"Triangular.h"

using namespace std;

vector<int> Triangular:: _elems;   //DO NOT LOSE DEFINITION HERE!!!

Triangular::Triangular(int len, int bp) //constructor
{
	_length = len>0 ? len : 1;
	_beg_pos = bp>0 ? bp : 1;
	Triangular::gen_elements(len);
	_next=_beg_pos-1;
}

bool Triangular::is_elem(int val)
{
	if(!_elems.size()||_elems[_elems.size()-1]<val)
	gen_elem_to_value(val);

	vector<int>::iterator found_it;
	vector<int>::iterator end_it=_elems.end();

	found_it=find(_elems.begin(),end_it,val);
	return found_it != end_it;
}

void Triangular::gen_elem_to_value(int val)
{
	int ix = _elems.size();

	while(ix<=2){
		_elems.push_back(1);
		ix++;
	}

	while(_elems[ix-1]<val&&ix<_max_elems){
		_elems.push_back(_elems[ix-1]+_elems[ix-2]);ix++;}
//	_elems.push_back(ix*(ix+1)/2);ix++;}

	if(ix == _max_elems)
		cerr<<"value too large"<<endl;   //cerr is in <iostream>
}

void Triangular::gen_elements(int val)
{
	int ix=_elems.size();
	if (val<=ix) return;

	if(val==1) {_elems.push_back(1); return;}
	if(val==2&&ix==0) {_elems.push_back(1); _elems.push_back(1); return;}
	if(val==2&&ix==1) {_elems.push_back(1); return;}

	//val>2
	while(ix<2){
		_elems.push_back(1);
		ix++;
	}

	while(ix<val&&ix<_max_elems){
		_elems.push_back(_elems[ix-1]+_elems[ix-2]);ix++;}

	if(ix == _max_elems)
		cerr<<"value too large"<<endl;   //cerr is in <iostream>
}