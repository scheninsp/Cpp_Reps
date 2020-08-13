#include<iostream>


using namespace std;

void swap(int* arr, int i, int j) {
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void print1d(int* arr, int len) {
	for (int i = 0; i < len; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void build_heap(int* arr, int len, int rt) {
	int left = rt * 2 + 1;
	int right = rt * 2 + 2;
	int target = rt;
	if (left < len) {
		if (arr[target] < arr[left]) {
			target = left;
		}
	}
	if (right < len) {
		if (arr[target] < arr[right]) {
			target = right;
		}
	}

	if (target != rt) {
		swap(arr, target, rt);
		//walk down
		build_heap(arr, len, target);
	}
}

void heap_sort(int* arr, int len) {
	for (int i = (len - 1) / 2; i >= 0; i--) { //walk up
		build_heap(arr, len, i);
	}

	for (int i = len - 1; i >= 0; i--) {
		swap(arr, 0, i);
		build_heap(arr, i, 0);
	}
}


int main() {

	const int LEN = 7;
	int arr[LEN] = { 9,2,5,4,2,8,1 };

	heap_sort(arr, LEN);

	print1d(arr, LEN);
	getchar();
	return 0;
}