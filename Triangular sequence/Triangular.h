#include<vector>
using namespace std;

class Triangular_iterator //iterator is defined before Triangular class for using it in the definition of Triangular class.
{

	friend class Triangular;

public:
	Triangular_iterator(int index) : _index(index-1) {};
	bool operator == (const Triangular_iterator&) const;
	bool operator != (const Triangular_iterator&) const;
	int operator *() const;
	Triangular_iterator& operator++();  //prefix version
	Triangular_iterator operator++(int); //postfix version

private:
	void check_integrity() const;
	int _index;
};


class Triangular
{
	friend int Triangular_iterator::operator*() const;
	friend void Triangular_iterator::check_integrity() const;

public:
	//bool next(int &val) const;
	//void next_reset() {int &val=_beg_pos;}
	static bool is_elem(int);
	static void gen_elem_to_value(int val);
	static void gen_elements(int);
	inline int length() {return _length;}
	Triangular(int len=1, int bp=1);

	typedef Triangular_iterator iterator;
	Triangular_iterator begin() const {return Triangular_iterator(_beg_pos);}
	Triangular_iterator end() const {return Triangular_iterator(_beg_pos+_length);}

private:
	int _next;
	int _beg_pos;
	int _length;
	static const int _max_elems = 1024; 
	static vector<int> _elems;
};   //DO NOT FORGET