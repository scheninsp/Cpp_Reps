//template binary tree, for implementation see red-black tree
#define _CRT_SECURE_NO_WARNINGS

#include<fstream>
#include<vector>
#include<iostream>

using namespace std;

short readFile(vector<vector<int>> &data) {
	ifstream frd("./input.txt");
	if (!frd) {
		return -1;
	}

	const int maxLine = 256;
	char buf[maxLine] = {0};
	char* tmp;

	while (frd.getline(buf, maxLine)) {
		vector<int> one_row;

		tmp = strtok(buf, " ");
		while (tmp) {
			int num = atoi(tmp);
			tmp = strtok(NULL, " ");
			one_row.push_back(num);
		}
		data.push_back(one_row);
	}

	return 0;
}


template <typename T>
class BinaryTree {
	
	template <typename T>
	class Node {
		friend class Heap_max; //for outer class to use private of inner, inner can freely use outer
	private:
		Node<T>* left;
		Node<T>* right;
		T val;
	public:
		Node():left(nullptr), right(nullptr), val(0) {};
		Node(T val) :left(nullptr), right(nullptr), val(val) {};
	};

private:
	Node<T> top;

public:
	//template <typename T>  //constructor don't need
	//Heap_max() { Node<T>(0); }; 
	BinaryTree() = delete;

	//template <typename T>  //constructor don't need
	BinaryTree(T val) {
		top = Node<T>(val);
	}

	template <typename T>
	T getTop(){
		return top.val;
	}

	template <typename T>
	void insertNode(T val) {
		Node(val);
	}

	
};

int main() {
	vector<vector<int>> data;
	readFile(data);
	int nTask = data.size();
	for (int iTask = 0; iTask < nTask; iTask++) {
		vector<int>::iterator iter = data[iTask].begin();
		BinaryTree<int> btree(*iter);
		
		int topnum = btree.getTop<int>(); //T as a return value, cannot be automatically deduced
		cout << topnum << endl;
	}

	getchar();
	return 0;

}