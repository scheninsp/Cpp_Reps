#include<iostream>
#include<vector>

using std::vector;
using std::cout;
using std::endl;

static void print1d(vector<int> &data) {
	for (int i = 0; i < data.size(); i++) {
		cout << data[i] << " ";
	}
	cout << endl;
}

static void adjust3nodes_rec(vector<int> &data, int heap_size, int root) {
	int left = 0;
	int right = 0;
	if (2 * root + 1 < heap_size) { left = 2 * root + 1; }
	if (2 * root + 2 < heap_size) { right = 2 * root + 2; }

	//swap root with max val
	int nroot = root;
	if (left > 0) { nroot = data[left] > data[nroot] ? left : nroot; }
	if (right > 0) { nroot = data[right] > data[nroot] ? right : nroot; }

	if (nroot != root) {
		int tmp = data[root];
		data[root] = data[nroot];
		data[nroot] = tmp;

		print1d(data);

		adjust3nodes_rec(data, heap_size, nroot); //recursively sort trees below
	}

}

static void buildHeap(vector<int> &data) {
	
	int rst = (data.size() - 1) / 2; 

	//adjust from bottom to top
	for (int i = rst; i >= 0; i--) {
		adjust3nodes_rec(data, data.size(), i);
	}

	//
	for (int i = data.size()-1; i>=0; i--) {
		int tmp = data[0];
		data[0] = data[i];
		data[i] = tmp;
		
		adjust3nodes_rec(data, i, 0);
	}
}



int main() {

	const int LEN = 10;

	int arr[LEN] = { 4,2,3,5,5,6,1,8,9,0 };

	vector<int> data(arr, arr + LEN);

	buildHeap(data);



	getchar();
	return 0;

}

