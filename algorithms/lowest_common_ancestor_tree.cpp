//lowest common ancestor
/*input:
1 2
2 3 4
3 4 5
4 5
5 6 7
6 7 8 9
7 8 9
*/

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<deque>
#include<fstream>
#include<cassert>
#include<unordered_map>

#define SIZE_T unsigned int

using std::vector;
using std::cout; 
using std::endl;
using std::string;
using std::deque;
using std::ifstream;
using std::ostream;
using std::unordered_map;
using std::pair;

enum Color { WHITE, BLACK };

//Node data is an array of type T
template<typename T>
class Node {
public:
	Node* lchild;
	Node* rchild;
	T* val;
	SIZE_T size;
	
	explicit Node(SIZE_T size) :size(size),lchild(nullptr),rchild(nullptr) {
		val = (T*)malloc(size * sizeof(T));
		memset(val, 0, size * sizeof(T));
	};

	explicit Node(vector<T> src) :size(src.size()), lchild(nullptr), rchild(nullptr) {
		val = (T*)malloc(size * sizeof(T));
		memset(val, 0, size * sizeof(T));
		for (SIZE_T i = 0; i < size; i++) {
			val[i] = src[i];
		}
	};

	~Node() {
		free(val);
	};
};

template<typename T>
ostream &operator<<(ostream &output, const Node<T> &thiz)
{
	output << reinterpret_cast<void *>(thiz.val);
	return output;
}

//Binary Tree
template<typename T>
class BinaryTree {
public:

	Node<T>* root;

	BinaryTree() :root(nullptr) {};
	explicit BinaryTree(Node<T>& node) :root(&node) {};
	explicit BinaryTree(Node<T>* pnode) :root(pnode) {};

	~BinaryTree() {
		if (root == nullptr) { return; }

		//last order traverse
		vector<Node<T>* > recycler;
		Node<T>* tmp = root;
		Node<T>* pre = nullptr;
		
		recycler.push_back(pre);
		recycler.push_back(tmp);

		while (true) {
			while(tmp->lchild != nullptr) {
				recycler.push_back(tmp->lchild);
				pre = tmp;
				tmp = tmp->lchild;
			}

			if (tmp->rchild == nullptr) {
				if (tmp == root) { 
					delete root; 
					break; 
				}

				assert(tmp == recycler.back());
				recycler.pop_back();

				assert((tmp == pre->lchild || tmp == pre->rchild) && tmp->lchild == nullptr);

				if (tmp == pre->lchild) { pre->lchild = nullptr; }
				else if (tmp == pre->rchild) { pre->rchild = nullptr; }

				cout << "delete :" << (*tmp) <<endl;
				delete tmp;

				tmp = recycler.back();
				
				recycler.pop_back();
				pre = recycler.back();
				recycler.push_back(tmp);

			}
			else {
				recycler.push_back(tmp->rchild);
				pre = tmp;
				tmp = tmp->rchild;
			}

		}

	};

	//insert only generate complete binary tree
	void insert(Node<T> * pnode) {
		if (root == nullptr) { root = pnode; return; }

		//level order traverse
		deque<Node<T>* > queue;
		queue.push_back(root); 
		int cur_level = 0;
		while(!queue.empty())
		{
			Node<T>* tmp = queue.front();
			queue.pop_front();

			if (tmp->lchild == nullptr) {
				tmp->lchild = pnode;
				break;
			}
			else if (tmp->rchild == nullptr) {
				tmp->rchild = pnode;
				break;
			}
			else {
				queue.push_back(tmp->lchild);
				queue.push_back(tmp->rchild);
			}
		}
	};
};

static void readFile(vector<vector<int>> &vec, string filename) {
	ifstream frd(filename);
	const int maxLine = 256;
	char buf[maxLine];
	char* tmp;
	
	int row = 0;
	while (frd.getline(buf, maxLine)) {
		vector<int> rowvec;
		tmp = strtok(buf, " ");
		while (tmp) {
			int num = atoi(tmp);
			rowvec.push_back(num);
			tmp = strtok(NULL, " ");
		}
		vec.push_back(rowvec);
		row++;
	}
};

//LCA Offline Tarjan
template<typename T>
class NodeInfo {
public:
	Color color;
	Node<T>* parent;
	int rank;
	Node<T>* nextChild;
	Node<T>* nextSibling;
	Node<T>* ancestor;

	NodeInfo() :color(WHITE), parent(nullptr), rank(0),
		nextChild(nullptr), nextSibling(nullptr), ancestor(nullptr) {};

	explicit NodeInfo(Node<T>* p) :color(WHITE), parent(nullptr), rank(0),
		nextChild(nullptr), nextSibling(nullptr), ancestor(nullptr) {};

};

template<typename T>
using map_T = unordered_map<Node<T>*, NodeInfo<T>>;

//initialize a node in set
template<typename T>
void makeSet(map_T<T> &subsets, Node<T>* pnode) {
	subsets[pnode].parent = pnode;
};

//find representative of a node
template<typename T>
Node<T>* findSet(map_T<T> &subsets, Node<T>* pnode) {
	if (subsets[pnode].parent != pnode){
		subsets[pnode].parent = findSet(subsets, subsets[pnode].parent);
	}
	return subsets[pnode].parent;
};

//union two sets where node1 and node2 lies in 
//caution pnode2 must be visited later than pnode1, to keep order in traverse
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


//initialize subsets, add all nodes to subset
//preprocess, find all nodes's next child or next sibling
//next child : left child -> (no left child) right child -> 0
//next sibling : right sibling -> 0
//in order traverse
template<typename T>
void initSet(map_T<T> &subsets, Node<T>* u) {
	if (u == nullptr) { return; }

	initSet(subsets, u->lchild);

	NodeInfo<T> nodeInfo(u);
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

};



template<typename T>
struct Query {
	Node<T>* L;
	Node<T>* R;

	Query(Node<T>* a, Node<T>* b) :L(a), R(b) {};
};

//LCA main process
//www.geeksforgeeks.org/tarjans-off-line-lowest-common-ancestors-algorithm/
template<typename T>
void lcaWalk(Node<T>* u, vector<Query<T>> q, map_T<T> &subsets) {
	makeSet(subsets, u);
	assert(subsets[u].color == WHITE);  //every node only visit once
	
	subsets[u].ancestor = u;
	Node<T>* child = subsets[u].nextChild;

	while (child != nullptr) {
		lcaWalk(child, q, subsets);
		unionSet(subsets, u, child);
		subsets[findSet(subsets, u)].ancestor = u;
		child = subsets[child].nextSibling;
	}

	subsets[u].color = BLACK;

	for (unsigned int i = 0; i < q.size(); i++) {
		if (u == q[i].L) {
			if (subsets[q[i].R].color == BLACK) {
				cout << subsets[findSet(subsets, q[i].R)].ancestor->val[0] << ":";
				cout << "(" << q[i].L->val[0] << ", " << q[i].R->val[0] << ")" << endl;
			}
		}

		else if (u == q[i].R) {
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
	for(unsigned int i = 0; i < arrays.size(); i++) {
		Node<int>* pnode = new Node<int>(arrays[i]);
		pnodeList.push_back(pnode);
	}
	cout << "before deletion" << endl;
	for (unsigned int i = 0; i < pnodeList.size(); i++) {
		cout << (*pnodeList[i]) << endl;
	}

	BinaryTree<int>* p_bTree = new BinaryTree<int>();
	for (unsigned int i = 0; i < pnodeList.size(); i++) {
		p_bTree->insert(pnodeList[i]);
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