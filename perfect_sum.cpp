//leetcode 377. Combination Sum IV
/*
Given an integer array with all positive numbers and no duplicates, find the number of possible combinations that add up to a positive integer target.

Example:

nums = [1, 2, 3]
target = 4

The possible combination ways are :
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

Note that different sequences are counted as different combinations.

Therefore the output is 7.
*/

#define _CRT_SECURE_NO_WARNINGS //for strtok()

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

short readFile(vector<vector<int>> &elements) {

	short errorcode = 0;

	ifstream frd("./input.txt");   //format: sum, elem1, elem2 ... elemN
	const int maxLine = 256;
	char buf[maxLine] = { 0 };
	char* tmp;

	while (frd.getline(buf, maxLine)) {
		vector<int> one_row;
		tmp = strtok(buf, " ");
		while (tmp) {
			int num = atoi(tmp);
			tmp = strtok(NULL, " ");
			one_row.push_back(num);
		}
		elements.push_back(one_row);
	}

	return errorcode;

};

//print 2d dp table
void print2d(bool** const dp, int imax, int jmax) {
	for (int i = 0; i < imax; i++) {
		for (int j = 0; j < jmax; j++) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
}

//print 1d vector
void print1dvec_reversed(vector<int> v) {
	for (int i = v.size()-1; i >= 0; i--) {
		cout << v[i] << " ";
	}
	cout << endl;
}

//recursively find subsets
bool printSubsetRec(const vector<int> v, int lastElem, int target_sum, bool** const dp, vector<int> result) {
	//v : sum, elem1, elem2, ...
	
	if (dp[lastElem][target_sum]) {
		if (lastElem > 0){
			for (int k = 0; k * v[lastElem+1] <= target_sum; k++) {
				if (dp[lastElem - 1][target_sum - k * v[lastElem+1]]) {
					result.push_back(k);
					cout << "dp[" << lastElem - 1 << "]" << "[" << target_sum - k * v[lastElem + 1]  <<"]" << endl;
					printSubsetRec(v, lastElem - 1, target_sum - k * v[lastElem+1], dp, result);
					result.pop_back();
				}
			}
		}
		else {  //lastElem=0, reach end of dp
			int k = target_sum / v[lastElem+1];
			result.push_back(k);
			print1dvec_reversed(result);
			result.pop_back();
			return true;
		}

	}
	
	return false;
}

int main() {
	vector<vector<int>> elements;

	short errorcode = readFile(elements);

	if (!errorcode) {
		for (int i = 0; i < elements.size(); i++) {
			for (int j = 0; j < elements[i].size(); j++) {
				cout << elements[i][j] << " ";
			}
			cout << endl;
		}
	}
	else {
		cout << "read error:" << errorcode << endl;
	}

	int nTask = elements.size();

	for (int iTask = 0; iTask < nTask; iTask++) {
		int nElems = elements[iTask].size() - 1;
		int target_sum = elements[iTask][0];
		
		bool** dp = new bool*[nElems];
		
		//initialize i=0
		dp[0] = new bool[target_sum + 1];
		for (int j = 0; j < target_sum + 1; j++) {
			if (j % elements[iTask][1] == 0)
				dp[0][j] = true;
			else
				dp[0][j] = false;
		}

		for (int i = 1; i < nElems; i++) {
			dp[i] = new bool[target_sum + 1];
			dp[i][0] = true;

			for (int j = 1; j < target_sum+1; j++) {
				dp[i][j] = false;
				int diff = 0;
				while (diff <= j) {
					dp[i][j] = dp[i][j] || dp[i - 1][j - diff];
					diff = diff + elements[iTask][i + 1];
				}
			}
		}

		print2d(dp, nElems, target_sum+1);

		
		if (dp[nElems-1][target_sum] == true) {
			vector<int> result;
			printSubsetRec(elements[iTask], nElems-1, target_sum, dp, result);
		}
		
		cout << "Task" << iTask << " finished" << endl;
		getchar();
	}
};