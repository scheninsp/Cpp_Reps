#include "nonblocking_queue.h"
#include<thread>

using std::thread;

int main() {

	NonBlockingQueue<int> nb_queue;

	int arr[] = { 1,2,3,4,5 };
	vector<int> data(arr, arr + 5);

	//reference to thread must use std::ref
	thread t1(test_push<int>, std::ref(nb_queue), std::ref(data));
	thread t2(test_pop<int>, std::ref(nb_queue));

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
};