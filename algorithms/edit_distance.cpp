//edit distance between strings.
// the minimum operations to transform one string into another, 
// using insert, remove, replace


//sample input:
/*
geek
gesek
cat
cut
sunday
saturday
*/

//sample output:
/*
1
1
3
*/


#include<fstream>
#include<iostream>
#include<vector>
#include<iterator>
#include<string>
#include <algorithm> //reverse

using namespace std;

void readFile(vector<string> &v) {
	ifstream ifs = ifstream("./input.txt");
	string s;
	istream_iterator<string> is(ifs);
	istream_iterator<string> eof;

	copy(is, eof, back_inserter(v));
}


int min(int x, int y, int z)
{
	return min(min(x, y), z);
}

int editDist(string str1, string str2, int m, int n)
{

	if (m == 0)
		return n;

	if (n == 0)
		return m;

	//last char equals
	if (str1[m - 1] == str2[n - 1])
		return editDist(str1, str2, m - 1, n - 1);

	//last char not equal
	return 1 + min(editDist(str1, str2, m, n - 1), // Insert 
		editDist(str1, str2, m - 1, n), // Remove 
		editDist(str1, str2, m - 1, n - 1) // Replace 
	);
}


int main() {
	vector<string> vstrings;
	readFile(vstrings);

	/*
	vector<string>::iterator iter;
	for (iter = vstrings.begin(); iter != vstrings.end(); iter++) {
		cout << *iter << endl;
	}*/

	int nTask = vstrings.size() / 2;

	for (int i = 0; i < nTask; i++) {
		string s1 = vstrings[2 * i];
		string s2 = vstrings[2 * i + 1];

		cout << "s1: " << s1 << endl;
		cout << "s2: " << s2 << endl;

		cout << editDist(s1, s2, s1.length(), s2.length());

		getchar();

	}

	return 0;
}
