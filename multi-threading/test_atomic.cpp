#include<atomic>
#include<iostream>

int main2() {

	std::atomic<int*> old_tail = nullptr;
	int* old_data = nullptr;

	int a = 108;
	int* new_data = &a;

	old_tail.compare_exchange_strong(old_data, new_data, std::memory_order_acquire, std::memory_order_relaxed);

	std::cout << *old_tail << std::endl;

	return 0;
}