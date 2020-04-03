//find first common node in list

#include<iostream>
#include<list>

using namespace std;

class Node {
public:
	int val;

	Node() :val(0){};

	Node(int v):val(v) {};

    Node* operator* () {
		return this;
	};

	Node& operator& () {
		return *this;
	};
	/*
	Node& operator= (const Node node) {
		(*this) = node;
		return (*this);
	};*/

	void deepcopy(const Node node) {
		val = node.val;
		return;
	};
};


int main() {
	Node Node1 = Node(1);
	cout << "Node1: " << *Node1 << endl;
	Node Node2 = Node(2);
	cout << "Node2: " << *Node2 << endl;
	Node1.deepcopy(Node2);
	cout << "deepcopy" << endl;
	cout << "Node1: " << *Node1 << endl;
	cout << "Node1 val: " << Node1.val << endl;

	Node Node3 = Node(3);
	swap(Node2, Node3); //swap with no overload move function will only exchange values not address
	//Node3 = move(Node2);  //move with no overload move function will only exchange values not address
	// an object never changes address in lifetime
	cout << "=" << endl;
	cout << "Node3: " << *Node3 << endl;
	cout << "Node3 val: " << Node3.val << endl;

	list<Node> list1;
	list<Node> list2;

	//build list
	for (int i = 0; i < 3; i++) {
		list1.push_back(Node());
	}

	for (int i = 0; i < 2; i++) {
		list2.push_back(Node());
	}

	Node commonNode1 = Node();
	cout << "common1: " << *commonNode1 << endl;

	list1.push_back(commonNode1);  //this calls copy constructor
	list2.push_back(commonNode1);

	for (int i = 0; i < 3; i++) {
		list1.push_back(Node());
	}

	for (int i = 0; i < 2; i++) {
		list2.push_back(Node());
	}

	Node commonNode2 = Node();

	list1.push_back(commonNode2);  
	list2.push_back(commonNode2);

	cout << "list1:";
	list<Node>::iterator iter1;
	for (iter1 = list1.begin(); iter1 != list1.end(); iter1++) {
		cout << *(*iter1) << " ";
	}
	cout << endl;

	cout << "list2:";
	list<Node>::iterator iter2;
	for (iter2 = list2.begin(); iter2 != list2.end(); iter2++) {
		cout << *(*iter2) << " ";
	}
	cout << endl;

	getchar();
	return 0;
}