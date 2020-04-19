#include "lockfree_queue.h"
#include<thread>

int main() {

	lock_free_queue<int> lfq;

	//lfq.push(1);

	//lfq.pop();

	int arr[] = { 1,2,3,4,5 };
	vector<int> data(arr, arr + 5);

	//reference to thread must use std::ref
	std::thread t1(test_push<int>, std::ref(lfq), std::ref(data));
	std::thread t2(test_pop<int>, std::ref(lfq));

	if (t1.joinable()) {
		t1.join();
	}

	if (t2.joinable()) {
		t2.join();
	}

	//cout << "finished" << endl;
	printf("finished");
	getchar();
	return 0;
}