#include<iostream>
#include<memory>
#include<windows.h>
#include<list>

class MyObj {
protected:
	int a;
	float b;
	double c;

public:
	MyObj() :a(0),b(0.0),c(0.0) {
		std::cout << "MyObj Constructor" << std::endl;
	};

	MyObj(int an, float bn, double cn) :a(an), b(bn), c(cn) {
		std::cout << "MyObj Constructor" << std::endl;
	};

	~MyObj() {
		std::cout << "MyObj Destructor" << std::endl;
	}

	void MyFunc1() {
		std::cout << "MyFunc1() Called" << std::endl;
	}

	friend std::ostream& operator<< (std::ostream& out, const MyObj& obj);
};

std::ostream& operator<< (std::ostream& out, const MyObj& obj) {
	out << obj.a << ' ' << obj.b << ' ' << obj.c << std::endl;
	return out;
};

//Constructor with no parameters
class MyObj_child : public MyObj {
protected:

	unsigned d;

public:
	MyObj_child() {
		std::cout << "MyObj_child Constructor" << std::endl;
	};

	MyObj_child(int an, float bn, double cn, unsigned dn) :MyObj(an, bn, cn), d(dn) {
		std::cout << "MyObj_child Constructor" << std::endl;
	};

	~MyObj_child() {
		std::cout << "MyObj_child Destructor" << std::endl;
	};

	friend std::ostream& operator<< (std::ostream& out, const MyObj_child& obj);
};

std::ostream& operator<< (std::ostream& out, const MyObj_child& obj) {
	out << obj.a << ' ' << obj.b << ' ' << obj.c << ' ' << obj.d << std::endl;
	return out;
};

//use copy to deliver shared_ptr
void test_shared1(std::shared_ptr<MyObj> sp) {
	if (sp) {
		sp->MyFunc1();
		std::cout << "sp use_count during test_shared : " << sp.use_count() << std::endl;
	}
	else {
		std::cout << "sp is nullptr" << std::endl;
	}
}

//use const & to deliver shared_ptr
void test_shared2(const std::shared_ptr<MyObj>& sp) {
	if (sp) {
		sp->MyFunc1();
		std::cout << "sp(const&) use_count during test_shared : " << sp.use_count() << std::endl;
	}
	else {
		std::cout << "sp is nullptr" << std::endl;
	}
}



void main() {

	//create a pointer container
	std::list<std::shared_ptr<MyObj>> ptr_manager;

	//MyObj obj1(0, 0., 0.);

	//Constructor
	//std::shared_ptr<MyObj> p1(new MyObj(0,0.,0.));
	//std::shared_ptr<MyObj> p2(new MyObj{});
	//std::shared_ptr<MyObj_child> p3 = std::make_shared<MyObj_child>();
	//std::shared_ptr<MyObj_child> p4 = std::make_shared<MyObj_child>(1,2.,3.,4);

	//polymorph
	std::shared_ptr<MyObj> p4 = std::make_shared<MyObj_child>();

	//ptr_manager.push_back(p1);
	//ptr_manager.push_back(p2);
	//ptr_manager.push_back(p3);

	//std::cout << "p1 " << *p1 << std::endl;
	//std::cout << "p2 " << *p2 << std::endl;
	//std::cout << "p3 " << *p3 << std::endl;
	std::cout << "p4 " << *p4 << std::endl;


	test_shared1(std::move(p4));  //release p4 after function call
	
	std::cout << "p4 use_count after test_shared : " << p4.use_count() << std::endl;

	//wait
	int cnt = 0;
	int waitMilliSeconds = 100;
	for (int i = 0; i < 10; i++) {
		Sleep(waitMilliSeconds);
	}

	//recheck list of smart ptrs
	for (std::list<std::shared_ptr<MyObj>>::iterator e = ptr_manager.begin();
		e != ptr_manager.end(); ++e) {
		std::cout << **e << std::endl;
	}

	//ptr_manager.pop_back();

	getchar();
	return;
}
