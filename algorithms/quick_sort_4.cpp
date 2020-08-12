#include<iostream>

inline void swap(int* arr, int a, int b) {
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

void quick_sort(int* arr, int l, int r) {
	int left = l;
	int right = r;
	int mid = (left + right) / 2;
	
	//move median to left and set left as pivot
	int pivot = mid;
	if (left > mid) { swap(arr, left, mid); }
	if (mid > right) { swap(arr, mid, right); }
	if (left > mid) { pivot = left; }
	else { pivot = mid; }

	while (left < right) {
		while (right > pivot && arr[right] > arr[pivot]) { right--; }
		swap(arr, right, pivot);
		while (left < pivot && arr[left] < arr[pivot]) { left++; }
		swap(arr, left, pivot);
	}

	if (left - 1 > l) {
		quick_sort(arr, l, left - 1);
	}
	if (right + 1 < r) {
		quick_sort(arr, right + 1, r);

	}
}

void main() {

	const int LEN = 12;
	int arr[LEN] = { 2,4,7,8,3,1,9,22,45,378,5654,24142 };

	quick_sort(arr, 0, LEN-1);

	for (int i = 0; i < LEN; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

	getchar();
}