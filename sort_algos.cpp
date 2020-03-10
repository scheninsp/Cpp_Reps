//implementing basic sortings
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
#include<vector>

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

inline void swap(vector<int> &arr, int x1, int x2) {
	if(x1==x2) return;
	arr[x1] = arr[x1] ^ arr[x2];
	arr[x2] = arr[x1] ^ arr[x2];
	arr[x1] = arr[x1] ^ arr[x2];
}

int partition(vector<int> &arr, int head, int tail) {
	
	if (tail - head > 1) {
		int mid = (head + tail) / 2;
		//get median from arr[head], arr[tail] , arr[mid]
		if (arr[head] > arr[mid]) { swap(arr, head, mid); }
		if (arr[mid] > arr[tail]) { swap(arr, mid, tail); }
		if (arr[head] > arr[mid]) { swap(arr, head, mid); }
		//move median to head
		swap(arr, head, mid);
	}
	int pivot = arr[head];

	while (head < tail) {
		while (head < tail && arr[tail] >= pivot) { tail--; }
		swap(arr, head, tail);

		while(head < tail && arr[head] <= pivot) { head++;}
		swap(arr, head, tail);
	}

	return head;
}

void quick_sort(vector<int> &arr) {

	vector<int> st; //saving current head and tail

	int head = 0;
	int tail = arr.size()-1;

	st.push_back(head);
	st.push_back(tail);

	while (!st.empty()) {
		tail = st.back();
		st.pop_back();
		head = st.back();
		st.pop_back();

		cout << "from " << head << " to " << tail << endl;
		int mid = partition(arr, head, tail);

		if (head < mid - 1) {
			st.push_back(head);
			st.push_back(mid - 1);
		}

		if (tail > mid + 1) {
			st.push_back(mid + 1);
			st.push_back(tail);
		}
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

		quick_sort(elements[iTask]);

		cout << "Sorted:";
		print1d(elements[iTask]);
	}

	getchar();

	return 0;
}


