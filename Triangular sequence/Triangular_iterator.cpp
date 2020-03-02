#include"Triangular.h"
#include<iostream>
using namespace std;

inline bool Triangular_iterator::operator ==(const Triangular_iterator &rhs) const {return _index == rhs._index;}
bool Triangular_iterator::operator !=(const Triangular_iterator &rhs) const {return !(*this == rhs);}

int Triangular_iterator::
	operator *() const 
{ 
	check_integrity(); 
return Triangular::_elems[_index];
}

 void Triangular_iterator::
	check_integrity() const
{
	if (_index >= Triangular::_max_elems)
	//throw iterator_overflow();
	cerr<<"iterator overflow";

	if (_index > Triangular::_elems.size())
		Triangular::gen_elements(_index+1);
}

Triangular_iterator& Triangular_iterator:: //why is there a '&'???
	operator ++() // return the next elem in sequence
{
	++_index;
	check_integrity();
	return *this;
}

inline Triangular_iterator Triangular_iterator::
	operator ++(int) 
{
	Triangular_iterator tmp = *this;
	++_index;
	check_integrity();
	return tmp;
}
