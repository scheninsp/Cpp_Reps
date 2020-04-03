//recusive version of quick_sort 
#include<iostream>

inline int get_median(int* array, int mid, int l, int r) {
	int tmp = 0;
	if (array[l] < array[mid]) { tmp = mid; mid = l; l = tmp; }
	if (array[r] < array[mid]) { tmp = mid; mid = r; r = tmp; }
	if (array[l] > array[r]) { return r; }
	else { return l; }
};

inline void swap(int* array, int i, int j) {
	if (i == j) { return; }
	array[i] ^= array[j];
	array[j] ^= array[i];
	array[i] ^= array[j];
};

static void print1d(int* array, int len) {
	for (int i = 0; i < len; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

static void quick_sort_rec(int* array, int l, int r) {
	std::cout << "(" << l << "," << r << ")" << std::endl;

	if (l == r) { return; }
	
	if (l == r - 1) {
		if (array[l] < array[r]) { 
			swap(array, l, r); 
			print1d(array, 10);
		}
		return;
	}

	int left = l;
	int right = r;
	int mid = (l + r) / 2;
	int pivot_indx = get_median(array,mid,l,r);
	int pivot = array[pivot_indx];

	//always move pivot to head position, 
	//swap happens between only head and tail
	swap(array, l, pivot_indx);

	while (l < r) {
		//if pivot is head, must start move from tail
		while (l < r && array[r] <= pivot) { r--; }
		swap(array, r, l);
		print1d(array, 10);

		while (l<r && array[l]>=pivot) { l++; }
		swap(array, l, r);
		print1d(array, 10);

	}

	if(l - 1 > left){
		quick_sort_rec(array, left, l - 1);
	 }
	if (l + 1 < right) {
		quick_sort_rec(array, l + 1, right);
	}

	return;
};



int main() {

	const int LEN = 10;

	int array[LEN] = { 2,5,3,5,6,1,4,9,7,8 };

	quick_sort_rec(array, 0, LEN-1);

	print1d(array, 10);

	getchar();
	return 0;
};