#include<iostream>
#include<algorithm>

using namespace std;

class AvlTree
{
	struct Node {
		int val;
		Node* left;
		Node* right;
		int height;

		Node(int v) :val(v), left(nullptr), right(nullptr),height(0) {};
	};

public:
	Node* root;

	AvlTree():root(nullptr) {};

	Node* rightRotate(Node* p) {
		Node* rt_left = p->left;
		Node* rt = p;
		Node* rt_left_right = p->left->right;
		p = rt_left;
		rt_left->right = rt;
		rt->left = rt_left_right;

		rt->height = max(get_height(rt->right), get_height(rt->left)) + 1;
		p->height = max(get_height(p->left), get_height(p->right)) + 1;

		return p;
	}

	Node* leftRotate(Node* p) {
		Node* rt_right = p->right;
		Node* rt = p;
		Node* rt_right_left = p->right->left;
		p = rt_right;
		rt_right->left = rt;
		rt->right = rt_right_left;

		rt->height = max(get_height(rt->right), get_height(rt->left))+1;
		p->height = max(get_height(p->left), get_height(p->right)) + 1;

		return p;
	}

	void delete_node(Node* p) {

	}

	void delete_tree(Node* rt) {

	}

	~AvlTree() {
		//last order traverse
		if (root != nullptr) {
			delete_tree(root);
		}
	}

	int get_height(Node* p) {
		if (p == nullptr) { return 0; }
		
		return p->height;
	}

	int get_balance(Node* p) {
		if (p == nullptr) { return 0; }

		return get_height(p->left) - get_height(p->right);
	}

	//recursively insert , return new root if adjusted
	Node* insert_node(Node* rt, Node* p) {
		if (rt == nullptr) {
			p->height = 1;
			return p;
		}

		if (p->val > rt->val) { rt->right = insert_node(rt->right, p); }
		else if (p->val < rt->val) { rt->left = insert_node(rt->left, p); }
		else { return rt; } //not allowed equal vals between nodes

		rt->height = 1 + max(get_height(rt->left), get_height(rt->right));

		int balance_factor = get_balance(rt);

		//L-L case
		if (balance_factor > 1 && p->val < rt->left->val) {
			return rightRotate(rt);
		}
		//L-R case
		if (balance_factor > 1 && p->val > rt->left->val) {
			rt->left = leftRotate(rt->left);
			return rightRotate(rt);
		}
		//R-L case
		if (balance_factor < -1 && p->val < rt->right->val) {
			rt->right = rightRotate(rt->right);
			return leftRotate(rt);
		}
		//R-R case
		if (balance_factor < -1 && p->val > rt->right->val) {
			return leftRotate(rt);
		}

		return rt;  //if nothing happens, normal insertion
	}

	void build(int* arr, int len) {
		root = new Node(arr[0]);
		for (int i = 1; i < len; i++) {			
			Node* tmp = new Node(arr[i]);
			root = insert_node(root, tmp);
			preOrder(root);
			cout << endl;
		}
	}

	void preOrder(Node *rt)
	{
		if (rt != NULL)
		{
			cout << rt->val << " ";
			preOrder(rt->left);
			preOrder(rt->right);
		}
	}

};

int main() {

	const int LEN = 7;
	int arr[LEN] = {10, 5, 15, 3, 8, 1, 2};

	AvlTree avltree = AvlTree();

	avltree.build(arr, LEN);

	getchar();
	return 0;
}