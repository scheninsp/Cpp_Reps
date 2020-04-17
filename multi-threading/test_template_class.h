#include<iostream>

template<typename T>
class fw {
private:
	T my_fw;

public:
	fw():my_fw(0) {};

	~fw() {};

	void print() {
		std::cout << static_cast<int>(my_fw) << std::endl;
	};
};

template<typename T>
static void test_fw(fw<T> obj_fw) {
	int x;
}




