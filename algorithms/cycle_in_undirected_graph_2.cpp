#include<iostream>
#include<vector>

using namespace std;

struct NodeInfo {
	int parent;
	int rank;

	NodeInfo() :parent(-1), rank(0) {};
	explicit NodeInfo(int p) :parent(p), rank(0) {};
};

void initSet(vector<NodeInfo> &subsets, int nNode) {
	for (unsigned int i = 0; i < nNode; i++) {
		subsets.push_back(NodeInfo(i));
	}
}

int findSet(vector<NodeInfo> &subsets, int n) {
	if (subsets[n].parent != n) {
		n = findSet(subsets, subsets[n].parent);
	}
	return n;
}

void unionSet(vector<NodeInfo> &subsets, int x, int y) {
	int xp = findSet(subsets, x);
	int yp = findSet(subsets, y);

	if (subsets[xp].rank > subsets[yp].rank) {
		subsets[yp].parent = xp;
	}
	else if (subsets[xp].rank < subsets[yp].rank) {
		subsets[xp].parent = yp;
	}
	else {
		subsets[yp].parent = xp;
		subsets[xp].rank++;
	}
}

class Graph {
	struct Edge {
		int p1, p2;
		Edge(int v, int w) :p1(v), p2(w) {};
	};

private:
	int nv, ne;
	vector<Edge> E;

public:
	Graph(int nv) :nv(nv), ne(0) {};

	Graph(int nv, int ne) :nv(nv), ne(ne) {};

	void addEdge(int v, int w) {
		E.push_back(Edge(v, w));
		ne++;
	};


	bool hasCycle() {
		vector<NodeInfo> subsets;
		initSet(subsets, nv);

		for (unsigned int i = 0; i < E.size(); i++) {
			if (findSet(subsets, E[i].p1) == findSet(subsets, E[i].p2)) { return true; }
			else(unionSet(subsets, E[i].p1, E[i].p2));
		}

		return false;
	};

};




int main() {
	//no direction graph
	Graph g1(3);
	g1.addEdge(0, 1);
	g1.addEdge(1, 2);
	g1.addEdge(2, 0);

	cout << "g1.hasCycle = " << g1.hasCycle() << endl;

	Graph g2(5);
	g1.addEdge(1, 0);
	g1.addEdge(1, 2);
	g1.addEdge(3, 4);

	cout << "g2.hasCycle = " << g2.hasCycle() << endl;

	getchar();
	return 0;
}
