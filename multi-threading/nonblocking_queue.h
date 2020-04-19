#pragma once
#define _ENABLE_ATOMIC_ALIGNMENT_FIX

#include <memory>
#include <atomic>
#include <vector>
#include <windows.h>

using std::shared_ptr;
using std::atomic;
using std::unique_ptr;
using std::memory_order_acquire;
using std::memory_order_relaxed;
using std::vector;

template <typename T>
class NonBlockingQueue {

private:
	struct node;
	//node ptr with counter
	struct counted_node_ptr {
		int external_count;
		node* ptr;
	};

	struct node_counter {  //32bit
		unsigned internal_count : 30;
		unsigned external_counters : 2;  //2bit
	};

	struct node {
		std::atomic<T*> data;
		std::atomic<node_counter> count;
		counted_node_ptr next;

		node() {
			node_counter new_count;
			new_count.internal_count = 0;
			new_count.external_counters = 2;
			//new node will be pointed by tail and second last node->next
			count.store(new_count);

			next.ptr = nullptr;
			next.external_count = 0;
		}

		//-- internal count
		void release_ref() {
			node_counter old_counter = count.load(memory_order_relaxed);
			node_counter new_counter;
			do {
				new_counter = old_counter;
				--new_counter.internal_count;
			} while (!count.compare_exchange_strong(old_counter, new_counter,
				memory_order_acquire, memory_order_relaxed));

			if (!new_counter.internal_count && !new_counter.external_counters) {
				delete this;
			}

		};
	};

	atomic<counted_node_ptr> head;
	atomic<counted_node_ptr> tail;
	
public:
	NonBlockingQueue();
	~NonBlockingQueue();

	bool empty();
	void push(T data);
	shared_ptr<T> pop();

	static void increase_external_count(atomic<counted_node_ptr>& counter,
		counted_node_ptr& old_counter);

	static void free_external_counter(counted_node_ptr &old_node_ptr);

};

//++external count
template <typename T>
void NonBlockingQueue<T>::increase_external_count(atomic<counted_node_ptr>& counter,
	counted_node_ptr& old_counter){

	counted_node_ptr new_counter;
	do {
		new_counter = old_counter;
		++new_counter.external_count;
	} while (!counter.compare_exchange_strong(
		old_counter, new_counter,
		memory_order_acquire, memory_order_relaxed));

	old_counter.external_count = new_counter.external_count;

};

//external_count --
//internal_count += (external_count-2)
template <typename T>
void NonBlockingQueue<T>::free_external_counter(counted_node_ptr &old_node_ptr) {
	node* const ptr = old_node_ptr.ptr;
	int const count_increase = old_node_ptr.external_count - 2;

	node_counter old_counter = ptr->count.load(memory_order_relaxed);
	node_counter new_counter;

	do {
		new_counter = old_counter;
		--new_counter.external_counters;
		new_counter.internal_count += count_increase;
	} while (!ptr->count.compare_exchange_strong(old_counter, new_counter,
		memory_order_acquire, memory_order_relaxed));

	if (!new_counter.internal_count && !new_counter.external_counters) {
		delete ptr;
	}
};

template<typename T>
NonBlockingQueue<T>::NonBlockingQueue():head(counted_node_ptr()), tail(head.load()) {
};

template<typename T>
NonBlockingQueue<T>::~NonBlockingQueue() {
	while (pop());
};

template <typename T>
bool NonBlockingQueue<T>::empty() {
	//Not Implemented
	return false;
};

template <typename T>
void NonBlockingQueue<T>::push(T data) {
	unique_ptr<T> new_data(new T(data));
	counted_node_ptr new_next;
	new_next.ptr = new node;
	new_next.external_count = 1;
	
	counted_node_ptr old_tail = tail.load();

	for (;;) {

		increase_external_count(tail, old_tail);

		T* old_data = nullptr;
		
		//OLD DATA =  NULLPTR CANNOT PERFORM
		if (old_tail.ptr->data.compare_exchange_strong(old_data, new_data.get())) {
			old_tail.ptr->next = new_next;
			old_tail = tail.exchange(new_next);

			free_external_counter(old_tail);
			new_data.release();
			break;
		}

		old_tail.ptr->release_ref();
	}

};

template <typename T>
shared_ptr<T> NonBlockingQueue<T>::pop() {
	counted_node_ptr old_head = head.load(memory_order_relaxed);
	for (;;) {
		increase_external_count(head, old_head);
		node* const ptr = old_head.ptr;

		if (ptr == tail.load().ptr) {
			ptr->release_ref();
			return unique_ptr<T>();
		}

		if (head.compare_exchange_strong(old_head, ptr->next)) {
			T* const res = ptr->data.exchange(nullptr);
			free_external_counter(old_head);
			return unique_ptr<T>(res);
		}

		ptr->release_ref();
	}
};


template<typename T>
static void test_push(NonBlockingQueue<T> &sync_queue, vector<T> &data) {
	for (vector<T>::iterator it = data.begin(); it != data.end(); it++) {
		// VS2017 bug : change property - language - fit pattern - not
		sync_queue.push(*it);
		//consequtive cout is slow, thread may change
		//cout << "push:" << *it << endl; 
		printf("push: %d\n", *it);
		Sleep(1000);
	}
};

template<typename T>
static void test_pop(NonBlockingQueue<T> &sync_queue) {
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