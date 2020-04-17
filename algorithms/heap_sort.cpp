//implementing basic sortings
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>

using namespace std;

short readFile(vector<vector<int>> &elements) {

	short errorcode = 0;

	ifstream frd("./input.txt");
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
}

void swap(vector<int> &data, int x1, int x2) {
	if (x1 == x2) { return; }
	data[x1] ^= data[x2];
	data[x2] ^= data[x1];
	data[x1] ^= data[x2];
}

void heapMaxSub(vector<int> &data, int l, int rt) {
	//sort the heap with root data[rt]
	//l : heap size
	//rt : heap root
	int l1 = 2 * rt + 1;
	int l2 = 2 * rt + 2;
	int imax = rt;

	if ((l > l1) && (data[l1] > data[imax])) { imax = l1; }
	if ((l > l2) && (data[l2] > data[imax])) { imax = l2; }

	if (imax != rt) {
		swap(data[imax], data[rt]);

		heapMaxSub(data, l, imax);
	}

}

//build heap inplace
void buildHeapMax(vector<int> &data) {
	int l = data.size();

	//This is indexing for complete binary tree
	for (int i = (l-1) / 2; i >= 0; i--) {
		heapMaxSub(data, l, i);
		//even if you start from the bottom layer H, 
		//after sorting layer H-1, layer H still has to be sorted
		//so heapMaxSub is recursive
	}

	for (int i = l - 1; i >= 0; i--) {

		swap(data, i, 0);   //current 0 is max, move to current end of heap
		heapMaxSub(data, i, 0);
	}
}


void print1d(const vector<int> &v) {
	vector<int>::const_iterator iter;
	for (iter = v.begin(); iter != v.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;

}

int main() {

	vector<vector<int>> elements;
	readFile(elements);

	int nTask = elements.size();

	for (int iTask = 0; iTask < nTask; iTask++) {
		cout << "Seq:";
		print1d(elements[iTask]);

		
		buildHeapMax(elements[iTask]);

		cout << "Sorted:";
		print1d(elements[iTask]);
	}

	getchar();

	return 0;
}

