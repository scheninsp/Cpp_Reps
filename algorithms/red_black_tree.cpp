//red black tree
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include<queue>

using namespace std;

class RBTree {
	enum Color {RED,BLACK};

	class Node {
		friend RBTree;
	private:
		Node* left;
		Node* right;
		Node* parent;
		bool color;
		int data;
	public:
		Node() :left(nullptr), right(nullptr), parent(nullptr), data(0),color(RED) {};
		Node(int val) :left(nullptr), right(nullptr), parent(nullptr), data(val), color(RED) {};
		Node(Node* l, Node* r, Node* p, int val) :left(l), right(r), parent(p), data(val), color(RED) {};
	};

private:
	Node* root;
protected:
	void rotateRight(Node*& rt, Node*& node3) {
		//before rotation
		//  3
		// 2 4
		//1
		//after rotation 
		//  2
		// 1 3
		//    4
		Node* node2 = node3->left;
		Node* node3_parent = node3->parent;

		node3->left = node2->right;
		if (node2->right != nullptr) {
			node2->right->parent = node3;
		}

		node3->parent = node2;
		node2->right = node3;
		node2->parent = node3_parent;

		if (node3_parent == nullptr) {
			rt = node2;
		}
		else if (node3_parent->left == node3) {
			node3_parent->left = node2;
		}
		else if (node3_parent->right == node3) {
			node3_parent->right = node2;
		}



	};

	void rotateLeft(Node*& rt, Node*& node2) {
		//before rotation
		//  2
		// 1 3
		//    4
		//after rotation 
		//  3
		// 2 4
		//1    

		Node* node3 = node2->right;
		Node* node2_parent = node2->parent;
		
		node2->right = node3->left;
		node3->left = node2;
		node3->parent = node2_parent;

		if (node3->left != nullptr) {
			node3->left->parent = node2;
		}
		node2->parent = node3;

		if (node2_parent == nullptr) {
			rt = node3;
		}
		else if (node2_parent->left == node2) {
			node2_parent->left = node3;
		}
		else if (node2_parent->right == node2) {
			node2_parent->right = node3;
		}

	};

	void fixViolation(Node*& rt, Node*& pt) {
		Node* pt_parent = nullptr;
		Node* pt_gparent = nullptr;

		while ((pt != rt) && (pt->color == RED) && (pt->parent->color == RED)){
			pt_parent = pt->parent;
			pt_gparent = pt_parent->parent; //if pt->parent->color == RED, must have grandparent

			//Case A: parent of pt is left child of gparent 
			if (pt_gparent->left == pt_parent) {
			
				Node* pt_uncle = pt_gparent->right;
			//Case A1: pt's uncle is red
				if (pt_uncle != nullptr && pt_uncle->color == RED) {
					pt_gparent->color = RED;
					pt_parent->color = BLACK;
					pt_uncle->color = BLACK;
					pt = pt_gparent;  //upward recursive
				}
				else {
				//Case A21: pt's uncle is black, pt is left child 
					if (pt_parent->left == pt) {
						rotateRight(rt, pt_gparent);
						pt_gparent->color = RED;
						pt_parent->color = BLACK;
						pt = pt_parent; 
					}
					
				//Case A22: pt's uncle is black, pt is right child
					else{
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
			else if (pt_gparent->right == pt_parent) {
				
				Node* pt_uncle = pt_gparent->left;
				//Case B1: pt's uncle is red
				if (pt_uncle != nullptr && pt_uncle->color == RED) {
					pt_gparent->color = RED;
					pt_parent->color = BLACK;
					pt_uncle->color = BLACK;
					pt = pt_gparent;  //upward recursive
				}
				else {
					//Case B21: pt's uncle is black, pt is right child 
					if (pt_parent->right == pt) {
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
			rt->left = BSTInsert(rt->left, pt);
			rt->left->parent = rt;
		}
		else if (pt->data > rt->data) {
			rt->right = BSTInsert(rt->right, pt);
			rt->right->parent = rt;
		}

		return rt;// trace back
	};

	//  Inorder trasversal(left-root-right)
	void inOrderHelper(Node* rt) {
		if (rt == nullptr) { return; }
		
		inOrderHelper(rt->left);
		cout << rt->data << " ";
		inOrderHelper(rt->right);
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

			if (temp->left != nullptr) { q.push(temp->left); }
			if (temp->right != nullptr) { q.push(temp->right); }

		}
	}

public:
	RBTree():root(nullptr) {};
	RBTree(Node &rt) {};

	Node* getRoot() { return root; }

	void insert(const int &data) {
		Node* pt = new Node(data);

		root = BSTInsert(root, pt);

		fixViolation(root, pt);
	};

	// inorder trasverse a binary tree gives sorted sequence
	void inOrder() { inOrderHelper(root);  cout << endl;};

	void levelOrder() { levelOrderHelper(root);  cout << endl;};
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