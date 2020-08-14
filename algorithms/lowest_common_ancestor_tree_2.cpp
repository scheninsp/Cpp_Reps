#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<fstream>
#include<unordered_map>
#include<cassert>

#define SIZE_T unsigned int

using namespace std;

template <typename T>
class Node {
public:
	Node* lchild;
	Node* rchild;
	T* val; 
	SIZE_T size;

public:
	explicit Node(SIZE_T s) : size(s), lchild(nullptr), rchild(nullptr) {
		val = (T*)malloc(size * sizeof(T));
		memset(val, 0, size * sizeof(T));
	};

	explicit Node(vector<T> src) : size(src.size()), lchild(nullptr), rchild(nullptr) {
		val = (T*)malloc(size * sizeof(T));
		memset(val, 0, size * sizeof(T));
		for (SIZE_T i = 0; i < size; i++) {
			val[i] = src[i];
		}
	};

	~Node() {
		free(val);
	}

};

template<typename T>
ostream & operator<< (ostream &output, const Node<T> &thiz) {
	output << reinterpret_cast<void*>(thiz.val);
	return output;
}

template <typename T>
class Query {
public:
	Node<T>* L;
	Node<T>* R;
	Query(Node<T>* l, Node<T>* r) :L(l), R(r) {};
};

enum Color{WHITE, BLACK};

template<typename T>
class NodeInfo {
public :
	Color color;
	Node<T>* parent;
	int rank;
	Node<T>* nextChild;
	Node<T>* nextSibling;
	Node<T>* ancestor;

	NodeInfo() :color(WHITE), parent(nullptr), rank(0),
		nextChild(nullptr), nextSibling(nullptr), ancestor(nullptr) {};
};

template<typename T>
class BinaryTree {
public:
	Node<T>* root;

public:
	BinaryTree() :root(nullptr) {};
	explicit BinaryTree(Node<T>& node) :root(&node) {};
	explicit BinaryTree(Node<T>* pnode) :root(pnode) {};

	~BinaryTree() {

		if (root == nullptr) { return; }

		lastOrderDeletion(root);

	}

	void insertAtNextSibling(Node<T>* pnode) {
		if (root == nullptr) { root = pnode;  return; }

		levelOrderInsert(pnode);
	}

private:

	void lastOrderDeletion(Node<T> * rt) {
		if (rt->lchild != nullptr) {
			lastOrderDeletion(rt->lchild);
		}
		if (rt->rchild != nullptr) {
			lastOrderDeletion(rt->rchild);
		}
		if (rt != nullptr) { 
			delete rt; 
		}
	}

	void levelOrderInsert(Node<T> *pnode) {
		
		queue<Node<T>*> level_queue;
		level_queue.push(root);


		while (!level_queue.empty()) {
			Node<T>* tmp = level_queue.front();
			level_queue.pop();
			if (tmp->lchild == nullptr) {
				tmp->lchild = pnode;
				break;
			}
			else if (tmp->rchild == nullptr) {
				tmp->rchild = pnode;
				break;
			}
			else {
				level_queue.push(tmp->lchild);
				level_queue.push(tmp->rchild);
			}
		}
	}



};

static void readFile(vector<vector<int>> &vec, string filename) {

	ifstream frd(filename);
	const int maxLine = 256;
	char buf[maxLine];
	char* tmp;

	int row = 0;
	while (frd.getline(buf, maxLine)) {
		vector<int> row_vec;
		tmp = strtok(buf, " ");
		while (tmp) {
			row_vec.push_back(atoi(tmp));
			tmp = strtok(NULL, " ");
		}
		vec.push_back(row_vec);
		row++;
	}

}

template<typename T>
using map_T = unordered_map<Node<T>*, NodeInfo<T>>;

template<typename T>
void initSet(map_T<T> &subsets, Node<T> *u) {

	if (u == nullptr) { return; }

	initSet(subsets, u->lchild);

	//fill nextChild and nextSibling in NodeInfo
	NodeInfo<T> nodeInfo;
	subsets.insert(pair<Node<T>*, NodeInfo<T>>(u, nodeInfo));

	if (u->lchild != nullptr && u->rchild != nullptr) {
		subsets[u].nextChild = u->lchild;
		assert(subsets.find(u->lchild) != subsets.end());  //lchild must have been in the map
		subsets[u->lchild].nextSibling = u->rchild;
	}
	else if (u->lchild != nullptr && u->rchild == nullptr) {
		subsets[u].nextChild = u->lchild;
	}
	else if (u->lchild == nullptr && u->rchild != nullptr) {
		subsets[u].nextChild = u->rchild;
	}
	else {
		//no process
	}

	initSet(subsets, u->rchild);

}

template<typename T>
void makeSet(map_T<T> &subsets, Node<T>* pnode) {
	subsets[pnode].parent = pnode;
};

template<typename T>
Node<T>* findSet(map_T<T> &subsets, Node<T>* pnode) {
	if (subsets[pnode].parent != pnode) {
		subsets[pnode].parent = findSet(subsets, subsets[pnode].parent);
	}
	return subsets[pnode].parent;
};

template<typename T>
void unionSet(map_T<T> &subsets, Node<T>* pnode1, Node<T>* pnode2) {
	Node<T>* pnode1_root = findSet(subsets, pnode1);
	Node<T>* pnode2_root = findSet(subsets, pnode2);

	if (subsets[pnode1_root].rank > subsets[pnode2_root].rank) {
		subsets[pnode2_root].parent = pnode1_root;
	}
	else if (subsets[pnode1_root].rank < subsets[pnode2_root].rank) {
		subsets[pnode1_root].parent = pnode2_root;
	}
	else {
		subsets[pnode2_root].parent = pnode1_root;
		subsets[pnode1_root].rank++;
	}
};


template<typename T>
void lcaWalk(Node<T>* u, vector<Query<T>> &q, map_T<T> &subsets) {
	makeSet(subsets, u);
	Node<T>* child = subsets[u].nextChild;

	while (child != nullptr) {
		lcaWalk(child, q, subsets);
		unionSet(subsets, u, child);
		subsets[findSet(subsets, u)].ancestor = u;
		child = subsets[child].nextSibling;
	}

	subsets[u].color = BLACK;

	for (unsigned int i = 0; i < q.size(); i++) {
		if(u == q[i].L){
			if (subsets[q[i].R].color == BLACK) {
				cout << subsets[findSet(subsets, q[i].R)].ancestor->val[0] << ":";
				cout << "(" << q[i].L->val[0] << ", " << q[i].R->val[0] << ")" << endl;
			}
		}

		if (u == q[i].R) {
			if (subsets[q[i].L].color == BLACK) {
				cout << subsets[findSet(subsets, q[i].L)].ancestor->val[0] << ":";
				cout << "(" << q[i].L->val[0] << ", " << q[i].R->val[0] << ")" << endl;
			}
		}
	}

}


int main() {

	vector<vector<int>> arrays;
	readFile(arrays, "input.txt");

	vector<Node<int>*> pnodeList;
	for (unsigned int i = 0; i < arrays.size(); i++) {
		Node<int>* pnode = new Node<int>(arrays[i]);
		pnodeList.push_back(pnode);
	}
	cout << "before deletion" << endl;
	for (unsigned int i = 0; i < pnodeList.size(); i++) {
		cout << (*pnodeList[i]) << endl;
	}

	BinaryTree<int>* p_bTree = new BinaryTree<int>();
	for (unsigned int i = 0; i < pnodeList.size(); i++) {
		p_bTree->insertAtNextSibling(pnodeList[i]);
	}

	vector<Query<int>> q;
	q.push_back(Query<int>(pnodeList[1], pnodeList[2]));
	q.push_back(Query<int>(pnodeList[3], pnodeList[6]));
	q.push_back(Query<int>(pnodeList[5], pnodeList[6]));

	
	map_T<int> subsets;
	initSet(subsets, p_bTree->root);

	cout << subsets[p_bTree->root].rank << endl;

	lcaWalk(p_bTree->root, q, subsets);

	cout << subsets[p_bTree->root].rank << endl;
	
	
	delete p_bTree;
	cout << "after deletion" << endl;
	for (unsigned int i = 0; i < pnodeList.size(); i++) {
		cout << (*pnodeList[i]) << endl;
	}  //all empty

	getchar();
	return 0;

}