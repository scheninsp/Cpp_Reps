#include<iostream>

using namespace std;

class Node {
public:
	int val;
	Node* next;

	Node() :val(0), next(nullptr) {};
	Node(int v) :val(v), next(nullptr) {};
	Node(int v, Node* ptr) :val(v), next(ptr) {};

};

class LinkedList {

public:
	Node* head;
	int len;

	LinkedList(int* array, int len):len(len) {
		head = new Node(array[0]);
		Node* p = head;
		for (int i = 1; i < len; i++) {
			Node* q = new Node(array[i]);
			p->next = q;
			p = q;
		}
	};

	~LinkedList() {
		for (int i = 0; i < len; i++) {
			Node* tmp = head;
			head = head->next;
			delete tmp;
		}
	};

	void insert(Node* n, int pos) {
		
		Node* p = head;
		for (int i = 0; i < pos-2; i++) {
			p = p->next;
		}
		Node* tmp = p->next;
		p->next = n;

		//incase Node has multiple descendents
		int cnt = 1;
		while (n->next != nullptr) {
			n = n->next;
			cnt++;
		}
		n->next = tmp;
		
		len += cnt;
	};

	void print() {
		Node* p = head;
		for (int i = 0; i < len; i++) {
			cout << p->val << " ";
			p = p->next;
		}
		cout << endl;
	}

};


int main() {
	const int LEN1 = 5;
	int array1[LEN1] = { 0,1,2,3,4 };

	const int LEN2 = 7;
	int array2[LEN2] = { 0,1,2,3,4,5,6 };
	
	const int LEN3 = 4;
	int array3[LEN3] = { 11,12,13,14 };

	LinkedList list1 = LinkedList(array1, LEN1);
	LinkedList list2 = LinkedList(array2, LEN2);
	LinkedList list3 = LinkedList(array3, LEN3);

	list1.insert(list3.head, LEN1 + 1);
	list2.insert(list3.head, LEN2 + 1);

	cout << "list1: ";
	list1.print();
	cout << "list2:";
	list2.print();

	int l1 = list1.len;
	int l2 = list2.len;
	int ldiff = l1 > l2 ? (l1 - l2) : (l2 - l1);
	
	Node* p1 = list1.head;
	Node* p2 = list2.head;
	if (l1 > l2) {
		for (int i = 0; i < ldiff; i++) {
			p1 = p1->next;
		}
	}
	if (l2 > l1) {
		for (int i = 0; i < ldiff; i++) {
			p2 = p2->next;
		}
	}
	while (p1 != nullptr && p2 != nullptr) {
		if (p1 == p2) {
			break;
		}
		p1 = p1->next;
		p2 = p2->next;
	}

	cout << "first common Node val: " << p1->val << endl;

	getchar();
	return 0;

};