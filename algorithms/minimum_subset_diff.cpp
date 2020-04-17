//partition a set into two subsets with minimum difference
//require output the difference

//exp.
//input: 1, 6, 11, 5
//output: 1
//Subset1 = { 1, 5, 6 }
//Subset2 = { 11 }

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

short readFile(vector<vector<int>> &elements) {

	short errorcode = 0;

	ifstream frd("./input.txt");   //format: sum, elem1, elem2 ... elemN
	if (!frd) {
		return -1;
	}

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


int findMinRec(int arr[], int i, int sc, int st)
{
	if (i == 0)
		return abs((st - sc) - sc);

	return min(findMinRec(arr, i - 1, sc + arr[i - 1], st),
		findMinRec(arr, i - 1, sc, st));
}

int findMin(int arr[], int n)
{
	int st = 0;
	for (int i = 0; i < n; i++)
		st += arr[i];

	return findMinRec(arr, n, 0, st);
}

// Driver program to test above function 
int main()
{
	int arr[] = { 1, 6, 11, 5 };
	int n = sizeof(arr) / sizeof(arr[0]);
	cout << "diff : " << findMin(arr, n) << endl;
	
	getchar();
	return 0;
}