// leetcode 894. n numbers , output all possibilities of complete binary tree

//exp. 
//input: 7
//output:
//[[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],
//[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]

#include<vector>
#include<iostream>
#include<deque>

using namespace std;

struct Node {
	Node* left = nullptr;
	Node* right = nullptr;
	int val = 0;
};

static vector<Node*> gen_all_tree_util(int n) {
	//cout << n << endl;

	//tree has saved all possible roots of current possible trees at n  
	vector<Node*> tree;
	if (n == 0) { return tree; }
	if (n == 1) { 
		Node* tmp = new Node();
		tree.push_back(tmp);
		return tree;
	}
	n = n - 1;
	for (int i = 1; i <= n; i+=2) {
		//cout << "left"<< endl;
		vector<Node*> left = gen_all_tree_util(i);
		//cout << "right" << endl;
		vector<Node*> right = gen_all_tree_util(n - i);
		for (Node* i : left) {
			for (Node* j : right) {
				Node* root = new Node();
				root->left = i;
				root->right = j;
				tree.push_back(root);
			}
		}
	}

	return tree;
}

//level order
static void print_tree(Node* root) {
	deque<Node*> queue;
	queue.push_back(root);

	while (!queue.empty()) {
		Node* tmp = queue.front();
		queue.pop_front();
		if (tmp != nullptr) { 
			cout << tmp->val << " "; 
			queue.push_back(tmp->left);
			queue.push_back(tmp->right);
		}
		else { cout << "null "; }
	}	

	cout << endl;
}

int main() {

	vector<Node*> tree = gen_all_tree_util(7);

	vector<Node*>::iterator iter;
	for (iter = tree.begin(); iter != tree.end(); iter++) {
		print_tree(*iter);
	}

	getchar();
	return 0;
}