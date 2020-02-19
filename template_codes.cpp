#include <vector>
#include <iostream>
#include <functional>  //less, greater
#include <algorithm>  //find_if

using std::vector;
using std::cout;
using std::endl;
using std::less;
using std::greater;

template <typename InputIterator, typename OutputIterator, 
		typename ElemType, typename Comp>
OutputIterator 
filter(InputIterator first, InputIterator last,
		OutputIterator at, const ElemType &val, Comp pred)
{
	while((first = find_if(first, last, bind2nd(pred, val))) != last){ 
		//find_if returns the first element satisfy pred(*iter, val)

		cout << "found value:" << *first << endl;
		*at++ = *first++;
	}
	return at;
}
int main()
{
	const int elem_size = 8;

	int ia[elem_size] = { 12, 8, 43, 0, 6, 21, 3, 7 };
	vector<int> ivec(ia, ia + elem_size);

	int ia2[elem_size];
	vector<int> ivec2(elem_size);
	
	cout << "filter integer array for values less than 8" << endl;
	filter(ia, ia + elem_size, ia2, elem_size, less<int>());

	cout << "filter integer vector for values greater than 8" << endl;
	filter(ivec.begin(), ivec.end(), ivec2.begin(), elem_size, greater<int>());

	getchar();
 }