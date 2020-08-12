//red black tree - rewrite
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<fstream>
#include<queue>

using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::queue;

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
		Node* root;

		void rotateRight(Node*& rt, Node*& node3){
			Node* node2 = node3->lchild;
			Node* node3_parent = node3->parent;

			if (node2->rchild != nullptr) {
				node2->rchild->parent = node3;
			}
			node3->parent = node2;
			node2->parent = node3_parent;

			node3->lchild = node2->rchild;
			node2->rchild = node3;

			if (node3_parent == nullptr) {
				//node3 is the original root
				rt = node2;
			}
			else if (node3_parent->lchild == node3) {
				node3_parent->lchild = node2;
			}
			else if (node3_parent->rchild == node3) {
				node3_parent->rchild = node2;
			}
		}


		void rotateLeft(Node*& rt, Node*& node2) {
			Node* node3 = node2->rchild;
			Node* node2_parent = node2->parent;

			if (node3->lchild != nullptr) {
				node3->lchild->parent = node2;
			}
			node2->parent = node3;
			node3->parent = node2_parent;

			node2->rchild = node3->lchild;
			node3->lchild = node2;

			if (node2_parent == nullptr) {
				//node2 is the original root
				rt = node3;
			}
			else if (node2_parent->lchild == node2) {
				node2_parent->lchild = node3;
			}
			else if (node2_parent->rchild == node2) {
				node2_parent->rchild = node3;
			}
		}

		void fixViolation(Node*& rt, Node*& pt) {
			Node* pt_parent = nullptr;
			Node* pt_gparent = nullptr;

			while ((pt != rt) && (pt->color == RED) && (pt->parent->color == RED)) {
				pt_parent = pt->parent;
				pt_gparent = pt_parent->parent; //if pt->parent->color == RED, must have grandparent

				//Case A: parent of pt is left child of gparent 
				if (pt_gparent->lchild == pt_parent) {

					Node* pt_uncle = pt_gparent->rchild;
					//Case A1: pt's uncle is red
					if (pt_uncle != nullptr && pt_uncle->color == RED) {
						pt_gparent->color = RED;
						pt_parent->color = BLACK;
						pt_uncle->color = BLACK;
						pt = pt_gparent;  //upward recursive
					}
					else {
						//Case A21: pt's uncle is black, pt is left child 
						if (pt_parent->lchild == pt) {
							rotateRight(rt, pt_gparent);
							pt_gparent->color = RED;
							pt_parent->color = BLACK;
							pt = pt_parent;
						}

						//Case A22: pt's uncle is black, pt is right child
						else {
							rotateLeft(rt, pt_parent);
							pt = pt_parent;
							pt_parent = pt->parent;
							rotateRight(rt, pt_gparent);
							pt_gparent->color = RED;
							pt_parent->color = BLACK;
							pt = pt_parent;
						}
					}

				}



				//Case B: parent of pt is right child of gparent 
				else if (pt_gparent->rchild == pt_parent) {

					Node* pt_uncle = pt_gparent->lchild;
					//Case B1: pt's uncle is red
					if (pt_uncle != nullptr && pt_uncle->color == RED) {
						pt_gparent->color = RED;
						pt_parent->color = BLACK;
						pt_uncle->color = BLACK;
						pt = pt_gparent;  //upward recursive
					}
					else {
						//Case B21: pt's uncle is black, pt is right child 
						if (pt_parent->rchild == pt) {
							rotateLeft(rt, pt_gparent);
							pt_gparent->color = RED;
							pt_parent->color = BLACK;
							pt = pt_parent;
						}

						//Case B22: pt's uncle is black, pt is left child
						else {
							rotateRight(rt, pt_parent);
							pt = pt_parent;
							pt_parent = pt->parent;
							rotateLeft(rt, pt_gparent);
							pt_gparent->color = RED;
							pt_parent->color = BLACK;
							pt = pt_parent;
						}
					}



				}

			}

			rt->color = BLACK;
		};

		//binary tree insert
		Node* BSTInsert(Node* rt, Node* pt) {
			if (rt == nullptr) { return pt; }

			if (pt->data < rt->data) {
				rt->lchild = BSTInsert(rt->lchild, pt);
				rt->lchild->parent = rt;
			}
			else if (pt->data > rt->data) {
				rt->rchild = BSTInsert(rt->rchild, pt);
				rt->rchild->parent = rt;
			}

			return rt;// trace back
		};

		//  Inorder trasversal(left-root-right)
		void inOrderHelper(Node* rt) {
			if (rt == nullptr) { return; }

			inOrderHelper(rt->lchild);
			cout << rt->data << " ";
			inOrderHelper(rt->rchild);
		}

		//level order trasversal
		void levelOrderHelper(Node* rt) {
			if (rt == nullptr) { return; }

			queue<Node *> q;
			q.push(rt);

			while (!q.empty()) {
				Node *temp = q.front();
				cout << temp->data << " ";
				q.pop();

				if (temp->lchild != nullptr) { q.push(temp->lchild); }
				if (temp->rchild != nullptr) { q.push(temp->rchild); }

			}
		}


	public:
		RBTree() :root(nullptr) {};
		RBTree(Node &rt) {};

		Node* getRoot() { return root; }

		void insert(const int &data) {
			Node* pt = new Node(data);

			root = BSTInsert(root, pt);

			fixViolation(root, pt);
		};

		// inorder trasverse a binary tree gives sorted sequence
		void inOrder() { inOrderHelper(root);  cout << endl; };

		void levelOrder() { levelOrderHelper(root);  cout << endl; };
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