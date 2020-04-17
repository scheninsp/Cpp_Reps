#include <cassert>
#include "shared_ptr_impl.h"
#include<iostream>
#include <string>

class TestMarker {
public:
	char marker;

	TestMarker(char mark) :marker(mark) {
		std::cout << "TestMarker Class Constructor" << std::endl;
	};
};


class TestBased {
public:
	virtual std::string name() const {
		return "TestBased";
	}

	virtual ~TestBased() { }
};

class TestDerived : public TestBased {
public:
	virtual std::string name() const {
		return "TestDerived";
	}
};

void test_copy_assignment() {
	scutil::SharedPtr<int> sp1(new int(111));
	scutil::SharedPtr<int> sp2;

	sp2 = sp1;

	assert(*sp1 == 111);
	assert(*sp1 == *sp2);
}

void test_copy_construction() {
	scutil::SharedPtr<int> sp1(new int(111));
	scutil::SharedPtr<int> sp2(sp1);

	assert(*sp1 == 111);
	assert(*sp1 == *sp2);
}

void test_get() {
	scutil::SharedPtr<int> sp(new int(111));

	assert(&(*sp) == sp.get());
}

void test_pointer_constructor() {
	scutil::SharedPtr<int> sp1(new int(1));
	assert(*sp1 == 1);

	scutil::SharedPtr<TestBased> sp2(new TestDerived);
	sp2->name() == "TestDerived";
}

void test_swap() {
	scutil::SharedPtr<int> sp1(new int(1));
	scutil::SharedPtr<int> sp2(new int(2));

	// Thanks to ADL the scutil::swap will be called
	swap(sp1, sp2);

	assert(*sp1 == 2);
	assert(*sp2 == 1);
}

void test_deleter() {
	int val = 1;

	auto deleter = [&val](int *ptr) -> void { val = 2; };

	{
		scutil::SharedPtr<int> sp(new int(), deleter);
	}

	assert(val == 2);
}


void test_make_shared() {
	auto ptr = scutil::make_shared<int>(10);
	std::cout << *ptr << std::endl;
	assert(*ptr == 10);
}

void test_make_shared_class1() {
	//only if args are provided, constructor is called
	auto ptr = scutil::make_shared<TestMarker>('M');
	//otherwise make_shared only assign a nullptr point to type TestMarker
	//auto ptr = scutil::make_shared<TestMarker>();

	std::cout << ptr->marker << std::endl;
	assert(ptr->marker == 'M');
}


int main() {

	test_copy_assignment();
	test_copy_construction();
	test_get();
	test_pointer_constructor();
	test_swap();
	test_deleter();
	test_make_shared();
	test_make_shared_class1();

	getchar();
	return 0;
}