#include<iostream>
#include<vector>
#include<fstream>

using std::vector;
using std::ifstream;
using std::cout;
using std::endl;

class RBTree {

	enum Color { RED, BLACK };

	class Node {
		friend RBTree;
	private:
		Node* lchild;
		Node* rchild;
		Node* parent;
		bool color;
		int data;
	public:
		Node() :lchild(nullptr), rchild(nullptr), parent(nullptr), color(RED), data(0) {};
		Node(int val) :lchild(nullptr), rchild(nullptr), parent(nullptr), color(RED), data(val) {};
		Node(Node* l , Node* r, Node* p, int val) :lchild(l), rchild(r), parent(p), color(RED), data(val) {};
	};

	private:
		Node* rt;

		rotateRight(Node*& rt, Node*& node3){
		}



	public:
		void insert(int data) {
		};

		void inOrder() {
		};

		void levelOrder() {
		};
};



short readFile(vector<vector<int>> &elements) {

	short errorcode = 0;

	ifstream frd("./input.txt");
	if (!frd) {
		return -1;
	}

	const int maxLine = 256;
	char buf[maxLine] = { 0 };
	char* tmp;

	while (frd.getline(buf, maxLine)) {
		vector<int> one_row;
		tmp = strtok(buf, " ");
		while (tmp) {
			int num = atoi(tmp);
			tmp = strtok(NULL, " ");
			one_row.push_back(num);
		}
		elements.push_back(one_row);
	}

	return errorcode;
}

void print1d(const vector<int> &v) {
	vector<int>::const_iterator iter;
	for (iter = v.begin(); iter != v.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;

}

int main() {

	vector<vector<int>> data;

	short errorcode = readFile(data);
	int nTask = data.size();

	for (int iTask = 0; iTask < nTask; iTask++) {

		cout << "Seq:";
		print1d(data[iTask]);
		cout << endl;

		RBTree rbTree = RBTree();
		for (unsigned i = 0; i < data[iTask].size(); i++) {
			rbTree.insert(data[iTask][i]);
		}

		cout << "inOrder:" << endl;
		rbTree.inOrder();

		cout << "levelOrder:" << endl;
		rbTree.levelOrder();

	}

	getchar();
	return 0;

}