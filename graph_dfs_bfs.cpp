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

		list<int>::iterator iter;
		for (iter = adj[v].begin(); iter != adj[v].end(); iter++) {
			if (visited[*iter] == false) {
				dfsUtil(*iter, visited);
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
		
		visited[v] = true;
		queue.push_back(v);

		list<int>::iterator iter;
		while (!queue.empty()) {
			
			int tmpv = queue.front();
			cout << tmpv << " ";

			queue.pop_front();

			for (iter = adj[tmpv].begin(); iter != adj[tmpv].end(); iter++)
			{
				if (!visited[*iter])
				{
					visited[*iter] = true;
					queue.push_back(*iter);
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