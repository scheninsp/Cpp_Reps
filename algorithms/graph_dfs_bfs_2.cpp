#include<iostream>
#include<list>

using namespace std;

class Graph {
private:
	int nv;
	list<int> *adj;

public:

	Graph(int n) :nv(n) { adj = new list<int>[nv]; };

	void addEdge(int v, int w) {
		adj[v].push_back(w);
	}

	void dfsUtil(int v, bool visited[]) {
		visited[v] = true;
		cout << v << " ";

		for (list<int>::iterator it = adj[v].begin(); it != adj[v].end(); it++) {
			if (!visited[*it]) {
				dfsUtil(*it, visited);
			}
		}
	}

	//DFS start from v
	void dfs(int v) {
		bool *visited = new bool[nv];

		for (int i = 0; i < nv; i++) {
			visited[i] = false;
		}

		dfsUtil(v, visited);
		cout << endl;
	}

	//BFS start from v
	void bfs(int v) {
		bool *visited = new bool[nv];

		for (int i = 0; i < nv; i++) {
			visited[i] = false;
		}

		list<int> queue;

		queue.push_back(v);

		while (!queue.empty()) {
			int u = queue.front();
			queue.pop_front();

			cout << u << " ";

			for (list<int>::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
				if (!visited[*it]) {
					visited[*it] = true;
					queue.push_back(*it);
				}
			}
		}

		cout << endl;

	}
};

int main() {
	Graph g(5);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(0, 3);
	g.addEdge(1, 3);
	g.addEdge(2, 3);
	g.addEdge(3, 4);

	g.dfs(0);
	g.bfs(0);

	getchar();
	return 0;
}