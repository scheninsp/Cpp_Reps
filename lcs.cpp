//longest common sequence
//question at: https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/

//sample input:
//abcdgh
//aedfhr
//aggtab
//gxtxayb

//sample output:
//adh
//gtab

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

//print 2d dp table
void print2d(int** const dp, int imax, int jmax) {
	for (int i = 0; i < imax; i++) {
		for (int j = 0; j < jmax; j++) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
}

void lcs_func(string s1, string s2, string &lcs) {
	int n1 = s1.size();
	int n2 = s2.size();
	//i=0, starts at first of longer seq

	int** dp = new int*[n1+1];
	for (int i = 0; i < n1+1; i++) {
		dp[i] = new int[n2+1];
	}
	//initialize
	for (int i = 0; i < n1 + 1; i++) {
		dp[i][0] = 0;
	}
	for (int j = 0; j < n2 + 1; j++) {
		dp[0][j] = 0;
	}
	
	//generate dp forward
	for (int i = 1; i < n1+1; i++) {
		for (int j = 1; j < n2+1; j++) {
			if (s1[i-1] == s2[j-1]) {  //dp[i][j] stands for string [i-1],[j-1] position
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];  //max
			}
		}
	}

	print2d(dp,n1+1,n2+1);

	//trace back to find lcs
	int iend = n1;
	int jend = n2;
	while (iend > 0) {
		while (jend > 0) {
			int x1 = dp[iend - 1][jend];
			int x2 = dp[iend][jend - 1];
			int x3 = dp[iend-1][jend-1];
			int x4 = dp[iend][jend];
			if (x1 == x4) { 
				iend--;
				continue;
			}		
			if (x2 == x4) {
				jend--;
				continue;
			}
			if (x3 == x4 - 1) {
				lcs.push_back(s1[iend-1]);
				iend--;
				jend--;
			}
		}
		if (iend == 0 || jend == 0) {
			break;
		}
	}

	reverse(lcs.begin(), lcs.end());
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
		string s1 = vstrings[2*i];
		string s2 = vstrings[2 * i + 1];
		
		cout << "s1: " << s1 << endl;
		cout << "s2: " << s2 << endl;

		string lcs = "";
		lcs_func(s1, s2, lcs);
		cout << "LCS: " << lcs << endl;

		getchar();

	}

	return 0;
}