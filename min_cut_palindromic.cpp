//return minimum cuts needed for a palindrome partitioning of string s
//exp.
//input : "aab"
//output : 1

#include<string>
#include<vector>
#include<iostream>

using namespace std;

int min_cut_util(string s, const vector<int> &dp) {
	if (s.size() == 1) { return 0; }

	//find (i, end) to be palindromic
	for (int i = 0; i <s.size()-1; i++) {
		int left = i;
		int right = s.size()-1;
		int mid = (left+right) / 2;
		if (s.size() % 2 == 0) { mid++; }  
		while (left < mid &&  s[left] == s[right]) {
			left++;
			right--;
		}
		if (left >= mid) {
			if (i == 0) { return 0; }
			else { return dp[i - 1] + 1; }
		}
	}

	return dp[s.size() - 2 ] + 1;
}

int min_cut_palindromic(string s) {

	int len = s.size();
	
	vector<int> dp;
	//mincut of substring at position (0,i)

	for (int i = 1; i < len+1; i++) {
		dp.push_back( min_cut_util(s.substr(0, i),dp) );
	}

	return dp[len-1];
}

int main(){

	string s1 = "aab";

	string s2 = "abaabbaacddc";

	cout << min_cut_palindromic(s1) << endl;
	cout << min_cut_palindromic(s2) << endl;

	getchar();
	return 0;

}