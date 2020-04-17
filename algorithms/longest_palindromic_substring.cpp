//Manacher's Algorithm for Longest Palindromic Substring

//exp,
//Input -> Output 
//babcbabcbaccba -> abcbabcba
//abaaba  -> abaaba
//abacdfgdcabba -> abba
//abacdedcaba  ->  abacdedcaba

#include <string>
#include <iostream>
#include <fstream>
#include<iterator>
#include <vector>
#include<algorithm>

using namespace std;

void readFile(vector<string> &v) {
	ifstream ifs = ifstream("./input.txt");
	string s;
	istream_iterator<string> is(ifs);
	istream_iterator<string> eof;

	copy(is, eof, back_inserter(v));
}

//Search for fitting substring 
int lpss_func(const string &s1, string &lpss) {
	
	int n = s1.length();
	if (n == 0)
		return -1;

	n = 2 * n + 1;  //expanded string 
	vector<int> L(n);

	L[0] = 0;
	L[1] = 1;
	int p0 = 1; 
	int p = 2; 
	int i = 0; 
	int iMirror; 
	int maxLPSLength = 0;
	int maxLPSCenterPosition = 0;
	int start = -1;
	int end = -1;
	int diff = -1;

	for (i = 2; i < n; i++)
	{
		iMirror = 2 * p0 - i;  //i mirror to p0
		L[i] = 0;

		if (i<p)   
			L[i] = min(L[iMirror], p-i);  //parts contained in both L[iMirror] and L[p0]


		while (((i + L[i]) < n && (i - L[i]) > 0) &&  //not reach the end
			(((i + L[i] + 1) % 2 == 0) ||    //is real character
			(s1[(i + L[i] + 1) / 2] == s1[(i - L[i] - 1) / 2])) )
		{
			L[i]++;
		}

		if (L[i] > maxLPSLength)  // record maxLPSLength 
		{
			maxLPSLength = L[i];
			maxLPSCenterPosition = i;
		}

		//set new right most palindromic substring
		if (i + L[i] > p)
		{
			p0 = i;
			p = i + L[i];
		}

	}

	start = (maxLPSCenterPosition - maxLPSLength) / 2;
	end = start + maxLPSLength - 1;

	for (i = start; i <= end; i++)
		lpss.push_back(s1[i]);

	return 0;
}

int main() {
	vector<string> vstrings;
	readFile(vstrings);

	int nTask = vstrings.size();

	for (int i = 0; i < nTask; i++) {
		string s1 = vstrings[i];

		cout << "input: " << s1 << endl;

		string lpss = "";
		lpss_func(s1, lpss);
		cout << "LPSS: " << lpss << endl;

		getchar();

	}

	return 0;
}