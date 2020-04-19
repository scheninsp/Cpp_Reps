// Listings 7.15-19, pp.212-217, Williams.
// Lock-free queue with reference counting.

//modified by chen song, runnable on windows 10
//2020.4.20

#define _ENABLE_ATOMIC_ALIGNMENT_FIX

#include <atomic>
#include <memory>
#include <vector>
#include<windows.h>
#include <stdio.h>

using std::vector;

template<typename T>
class lock_free_queue
{
private:
	struct node;

	struct counted_node_ptr
	{
		int external_count;
		node* ptr;

		counted_node_ptr() :external_count(0), ptr(nullptr) {};

		counted_node_ptr(node* p):external_count(0), ptr(p) {};
	};
	std::atomic<counted_node_ptr> head;
	std::atomic<counted_node_ptr> tail;

	struct node_counter
	{
		unsigned internal_count : 30;
		unsigned external_counters : 2;
	};

	struct node
	{
		std::atomic<T*> data;
		std::atomic<node_counter> count;
		counted_node_ptr next;
		node()
		{
			data = nullptr;
			node_counter new_count;
			new_count.internal_count = 0;
			new_count.external_counters = 2;
			count.store(new_count);
			next.ptr = nullptr;
			next.external_count = 0;
		};

		void release_ref()
		{
			node_counter old_counter =
				count.load(std::memory_order_relaxed);
			node_counter new_counter;
			do
			{
				new_counter = old_counter;
				--new_counter.internal_count;
			} while (!count.compare_exchange_strong(
				old_counter, new_counter,
				std::memory_order_acquire, std::memory_order_relaxed));
			if (!new_counter.internal_count &&
				!new_counter.external_counters)
			{
				delete this;
			}
		};
	};


	static void increase_external_count(
		std::atomic<counted_node_ptr>& counter,
		counted_node_ptr& old_counter)
	{
		counted_node_ptr new_counter;
		do
		{
			new_counter = old_counter;
			++new_counter.external_count;
		} while (!counter.compare_exchange_strong(
			old_counter, new_counter,
			std::memory_order_acquire, std::memory_order_relaxed));
		old_counter.external_count = new_counter.external_count;
	}

	static void free_external_counter(counted_node_ptr &old_node_ptr)
	{
		node* const ptr = old_node_ptr.ptr;
		int const count_increase = old_node_ptr.external_count - 2;
		node_counter old_counter =
			ptr->count.load(std::memory_order_relaxed);
		node_counter new_counter;
		do
		{
			new_counter = old_counter;
			--new_counter.external_counters;
			new_counter.internal_count += count_increase;
		} while (!ptr->count.compare_exchange_strong(
			old_counter, new_counter,
			std::memory_order_acquire, std::memory_order_relaxed));
		if (!new_counter.internal_count &&
			!new_counter.external_counters)
		{
			delete ptr;
		}
	}

public:
	lock_free_queue(): head(counted_node_ptr()), tail(head.load()) {
		//must be put into intialization list
		//std::atomic<counted_node_ptr> head(counted_node_ptr());
		//std::atomic<counted_node_ptr> tail(counted_node_ptr());

		node* ptr = new node;
		counted_node_ptr tmp (ptr);
		head.store(tmp);
		tail.store(tmp);

	}
	lock_free_queue(const lock_free_queue& other) = delete;
	lock_free_queue& operator=(const lock_free_queue& other) = delete;
	
	~lock_free_queue()
	{
		while (pop());
	}

	void push(T new_value)
	{
		std::unique_ptr<T> new_data(new T(new_value));
		counted_node_ptr new_next;
		new_next.ptr = new node;
		new_next.external_count = 1;
		counted_node_ptr old_tail = tail.load();
		for (;;)
		{
			increase_external_count(tail, old_tail);
			T* old_data = nullptr;
			if (old_tail.ptr->data.compare_exchange_strong(
				old_data, new_data.get()))
			{
				old_tail.ptr->next = new_next;
				old_tail = tail.exchange(new_next);
				free_external_counter(old_tail);
				new_data.release();
				break;
			}
			old_tail.ptr->release_ref();
		}
	}

	std::unique_ptr<T> pop()
	{
		counted_node_ptr old_head = head.load(std::memory_order_relaxed);
		for (;;)
		{
			increase_external_count(head, old_head);
			node* const ptr = old_head.ptr;
			if (ptr == tail.load().ptr)
			{
				ptr->release_ref();
				return std::unique_ptr<T>();
			}
			if (head.compare_exchange_strong(old_head, ptr->next))
			{
				T* const res = ptr->data.exchange(nullptr);
				free_external_counter(old_head);
				return std::unique_ptr<T>(res);
			}
			ptr->release_ref();
		}
	}

	bool empty() {
		counted_node_ptr old_head = head.load(std::memory_order_relaxed);
		node* const ptr = old_head.ptr;
		if (ptr == tail.load().ptr) {
			return true;
		}
		else {
			return false;
		}
	}
};



template<typename T>
static void test_push(lock_free_queue<T> &sync_queue, vector<T> &data) {
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
static void test_pop(lock_free_queue<T> &sync_queue) {
	clock_t clockBegin, clockEnd;
	clockBegin = clock();
	while (true) {
		while (!sync_queue.empty()) {
			std::shared_ptr<T> data = sync_queue.pop();
			//cout << "pop:" << *data << endl;
			printf("pop: %d\n", *data);
		}
		clockEnd = clock();
		if (clockEnd - clockBegin > 6000) {
			break;
		}
	}
};
