//www.geeksforgeeks.org/tarjans-off-line-lowest-common-ancestors-algorithm/ 
//A C++ Program to implement Tarjan Offline LCA Algorithm 
//Only for process show
/*
性质：
所有属于union set 的元素，有共同的parent = p (p不一定是最顶层的)
后序遍历，所有遍历过的元素是black。所有black元素的子树都是black。
当前正在分析的元素u，和任意一个Black元素 v的最近公共祖先就是 v所在集合的 parent 的 ancestor， 即 p = findSet(subsets, v); p.ancestor 。
*/

#include <stdio.h>
#include <memory>
#include<iostream>

#define V 9	 // number of nodes in input tree 
#define WHITE 1 // COLOUR 'WHITE' is assigned value 1 
#define BLACK 2 // COLOUR 'BLACK' is assigned value 2 

using std::cout;
using std::endl;

/* A binary tree node has data, pointer to left child
and a pointer to right child */
struct Node
{
	int data;
	Node* left, *right;
};

/*
subset[i].parent-->Holds the parent of node-'i'
subset[i].rank-->Holds the rank of node-'i'
subset[i].ancestor-->Holds the LCA queries answers
subset[i].child-->Holds one of the child of node-'i'
					if present, else -'0'
subset[i].sibling-->Holds the right-sibling of node-'i'
					if present, else -'0'
subset[i].color-->Holds the colour of node-'i'
*/
struct subset
{
	int parent, rank, ancestor, child, sibling, color;
};

// Structure to represent a query 
// A query consists of (L,R) and we will process the 
// queries offline a/c to Tarjan's oflline LCA algorithm 
struct Query
{
	int L, R;
};

/* Helper function that allocates a new node with the
given data and NULL left and right pointers. */
Node* newNode(int data)
{
	Node* node = new Node;
	node->data = data;
	node->left = node->right = NULL;
	return(node);
}

//A utility function to make set 
void makeSet(struct subset subsets[], int i)
{
	if (i < 1 || i > V)
		return;

	subsets[i].color = WHITE;
	subsets[i].parent = i;
	subsets[i].rank = 0;

	return;
}

// A utility function to find set of an element i 
// (uses path compression technique) 
int findSet(struct subset subsets[], int i)
{

	// find root and make root as parent of i (path compression) 
	if (subsets[i].parent != i)
		subsets[i].parent = findSet(subsets, subsets[i].parent);

	return subsets[i].parent;
}

// A function that does union of two sets of x and y 
// (uses union by rank) 
void unionSet(struct subset subsets[], int x, int y)
{
	int xroot = findSet(subsets, x);
	int yroot = findSet(subsets, y);

	// Attach smaller rank tree under root of high rank tree 
	// (Union by Rank) 
	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;

	// If ranks are same, then make one as root and increment 
	// its rank by one 
	else
	{
		subsets[yroot].parent = xroot;
		(subsets[xroot].rank)++;
	}
}

// The main function that prints LCAs. u is root's data. 
// m is size of q[] 
void lcaWalk(int u, struct Query q[], int m,
	struct subset subsets[])
{
	// Make Sets 
	makeSet(subsets, u);

	// Initially, each node's ancestor is the node 
	// itself. 
	//subsets[findSet(subsets, u)].ancestor = u;
	subsets[u].ancestor = u;

	for (int i = 1; i <= V; i++) {
		cout << i << " ancestor: " << subsets[i].ancestor << endl;
	}
	cout << endl;

	int child = subsets[u].child;

	if (u == 7) {
		cout << "at u=7" << endl;
	}

	// This while loop doesn't run for more than 2 times 
	// as there can be at max. two children of a node 
	while (child != 0)
	{
		lcaWalk(child, q, m, subsets);
		cout << "union(" << u << "," << child << ")" << endl;
		unionSet(subsets, u, child);
		for (int i = 1; i <= V; i++) {
			cout << i << " parent: " << subsets[i].parent << endl;
		}
		cout << endl;

		cout << findSet(subsets, u) << " = findSet(" << u << ")" << endl;
		subsets[findSet(subsets, u)].ancestor = u;

		for (int i = 1; i <= V; i++) {
			cout << i << " ancestor: " << subsets[i].ancestor << endl;
		}
		cout << endl;

		child = subsets[child].sibling;
	}


	subsets[u].color = BLACK;
	for (int i = 1; i <= V; i++) {
		cout << i << " color: " << subsets[i].color << endl;
	}
	cout << endl;

	for (int i = 0; i < m; i++)
	{
		if (q[i].L == u)
		{
			if (subsets[q[i].R].color == BLACK)
			{
				cout << findSet(subsets, q[i].R) << endl;
				printf("LCA(%d %d) -> %d\n",
					q[i].L,
					q[i].R,
					subsets[findSet(subsets, q[i].R)].ancestor);
			}
		}
		else if (q[i].R == u)
		{
			if (subsets[q[i].L].color == BLACK)
			{
				cout << findSet(subsets, q[i].L) << endl;
				printf("LCA(%d %d) -> %d\n",
					q[i].L,
					q[i].R,
					subsets[findSet(subsets, q[i].L)].ancestor);
			}
		}
	}

	return;
}

// This is basically an inorder traversal and 
// we preprocess the arrays-> child[] 
// and sibling[] in "struct subset" with 
// the tree structure using this function. 
void preprocess(Node * node, struct subset subsets[])
{
	if (node == NULL)
		return;

	// Recur on left child 
	preprocess(node->left, subsets);

	if (node->left != NULL && node->right != NULL)
	{
		/* Note that the below two lines can also be this-
		subsets[node->data].child = node->right->data;
		subsets[node->right->data].sibling =
										node->left->data;

		This is because if both left and right children of
		node-'i' are present then we can store any of them
		in subsets[i].child and correspondingly its sibling*/
		subsets[node->data].child = node->left->data;
		subsets[node->left->data].sibling =
			node->right->data;

	}
	else if ((node->left != NULL && node->right == NULL)
		|| (node->left == NULL && node->right != NULL))
	{
		if (node->left != NULL && node->right == NULL)
			subsets[node->data].child = node->left->data;
		else
			subsets[node->data].child = node->right->data;
	}

	//Recur on right child 
	preprocess(node->right, subsets);
}

// A function to initialise prior to pre-processing and 
// LCA walk 
void initialise(struct subset subsets[])
{
	// Initialising the structure with 0's 
	memset(subsets, 0, (V + 1) * sizeof(struct subset));

	// We colour all nodes WHITE before LCA Walk. 
	for (int i = 1; i <= V; i++)
		subsets[i].color = WHITE;

	return;
}

// Prints LCAs for given queries q[0..m-1] in a tree 
// with given root 
void printLCAs(Node *root, Query q[], int m)
{
	// Allocate memory for V subsets and nodes 
	struct subset * subsets = new subset[V + 1];

	// Creates subsets and colors them WHITE 
	initialise(subsets);

	// Preprocess the tree 
	preprocess(root, subsets);

	// Perform a tree walk to process the LCA queries 
	// offline 
	lcaWalk(root->data, q, m, subsets);
}

// Driver program to test above functions 
int main()
{
	/*
	We construct a binary tree :-
			1
		/ \
		2 3
	/ \    / \
	4 5	  6   7
	         / \
			 8  9
	*/

	Node *root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);
	root->right->left = newNode(6);
	root->right->right = newNode(7);
	root->right->right->left = newNode(8);
	root->right->right->right = newNode(9);

	// LCA Queries to answer 
	//Query q[] = { {5, 4}, {1, 3}, {2, 3}, {4, 7} };
	Query q[] = { {4,5}, {8, 7} };
	int m = sizeof(q) / sizeof(q[0]);

	printLCAs(root, q, m);

	return 0;
}
