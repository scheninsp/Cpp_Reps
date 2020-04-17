#pragma once

#include<stdio.h>
#include<memory>
#include<queue>
#include<mutex>
#include<thread>
#include<vector>
#include<windows.h>  //timer

using std::shared_ptr;
using std::queue;
using std::mutex;
using std::lock_guard;
using std::move;
using std::make_shared;
using std::condition_variable;
using std::thread;
using std::vector;
using std::unique_lock;

template <typename T>
class SyncQueue {
private:
	queue<shared_ptr<T>> m_queue;
	mutex m_lock;
	condition_variable m_cond;

public:
	//template<typename T>
	SyncQueue() {};
	~SyncQueue() {};

	bool empty();
	void push(T data);
	shared_ptr<T> pop();

};

template<typename T>
bool SyncQueue<T>::empty() {
	lock_guard<mutex> lk(m_lock);
	return m_queue.empty();
};

template<typename T>
void SyncQueue<T>::push(T data) {
	shared_ptr<T> in_data(make_shared<T>(move(data)));
	lock_guard<mutex> lk(m_lock);
	m_queue.push(in_data);
}

template<typename T>
shared_ptr<T> SyncQueue<T>::pop() {
	unique_lock<mutex> lk(m_lock);
	m_cond.wait(lk, [this] {return !m_queue.empty(); });  //anonymous function 
	shared_ptr<T> res = m_queue.front();
	m_queue.pop();
	return res;
};

template<typename T>
static void test_push(SyncQueue<T> &sync_queue, vector<T> &data) {
	for (vector<T>::iterator it = data.begin(); it != data.end(); it++) {
		// VS2017 bug : change property - language - fit pattern - not
		sync_queue.push( *it );
		//consequtive cout is slow, thread may change
		//cout << "push:" << *it << endl; 
		printf("push: %d\n", *it);
		Sleep(1000);
	}
};

template<typename T>
static void test_pop(SyncQueue<T> &sync_queue) {
	clock_t clockBegin, clockEnd;
	clockBegin = clock();
	while (true) {
		while (!sync_queue.empty()) {
			shared_ptr<T> data = sync_queue.pop();
			//cout << "pop:" << *data << endl;
			printf("pop: %d\n", *data);
		}
		clockEnd = clock();
		if (clockEnd - clockBegin > 6000) {
			break;
		}
	}
};
