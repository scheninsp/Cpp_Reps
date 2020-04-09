//toposort
// topoSort_dfs output:
//4 5 0 2 3 1 

// topoSortAll output:
//4 5 0 2 3 1 
//4 5 2 0 3 1
//...
//5 4 2 3 0 1
//5 4 2 3 1 0

#include<iostream>
#include<list>
#include<vector>

using namespace std;

class Graph {
private:
	int nv;
	list<int> *adj;

public:

	Graph(int n) :nv(n) {
		adj = new list<int>[nv];
	};

	~Graph() {
		delete[] adj;
	}

	void addEdge(int v, int w) {
		adj[v].push_back(w);
	};

	void initIndegree(int* indegree){
		for (int i = 0; i < nv; i++) {
			for (list<int>::iterator it = adj[i].begin(); it != adj[i].end(); it++) {
				indegree[*it]++;
			}
		}
	}

	void topoSortUtil_dfs(int src, bool* visited, vector<int> &res) {
		visited[src] = true;
		for (list<int>::iterator it = adj[src].begin(); it != adj[src].end(); it++) {
			if (visited[*it] == false) {
				topoSortUtil_dfs(*it, visited, res);
			}
		}
		res.push_back(src);
	}

	//return only one possibility of toposort
	void topoSort_dfs() {
		//find zero preceder vertex
		int* indegree = new int[nv];
		for (int i = 0; i < nv; i++) {
			indegree[i] = 0;
		}
		initIndegree(indegree);
		
		vector<int> src_vec;
		for (int i = 0; i < nv; i++) {
			if (indegree[i] == 0) {
				src_vec.push_back(i);
			}
		}

		//			
		vector<int> res;
		bool* visited = new bool[nv];
		for (int i = 0; i < nv; i++) {
			visited[i] = false;
		}
		while (!src_vec.empty()) {
			int src = src_vec.back();
			src_vec.pop_back();

			topoSortUtil_dfs(src, visited, res);
		}

		while (!res.empty()) {
			int tmp = res.back();
			res.pop_back();
			visited[tmp] = false;
			cout << tmp << " ";
		}
		cout << endl;

		delete[] visited;
		delete[] indegree;
	};

	//generate all possiblities 
	void topoSortAllUtil(int* indegree, bool* visited, vector<int> &res) {
		for (int i = 0; i < nv; i++) {
			if (indegree[i]==0 && !visited[i]) {
				for (list<int>::iterator it = adj[i].begin(); it != adj[i].end(); it++) {
					indegree[*it]--;
				}

				res.push_back(i);
				visited[i] = true;
				topoSortAllUtil(indegree, visited, res);

				res.pop_back();
				visited[i] = false;
				for (list<int>::iterator it = adj[i].begin(); it != adj[i].end(); it++) {
					indegree[*it]++;
				}
			}
		}

		for (vector<int>::iterator it = res.begin(); it != res.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	};

	void topoSortAll() {
		int* indegree = new int[nv];
		for (int i = 0; i < nv; i++) {
			indegree[i] = 0;
		}
		initIndegree(indegree);

		bool* visited = new bool[nv];
		for (int i = 0; i < nv; i++) {
			visited[i] = false;
		}

		vector<int> res;
		topoSortAllUtil(indegree, visited, res);

		delete[] visited;
		delete[] indegree;
	};

};


int main() {
	Graph g(6);
	g.addEdge(5, 2);
	g.addEdge(5, 0);
	g.addEdge(4, 0);
	g.addEdge(4, 1);
	g.addEdge(2, 3);
	g.addEdge(3, 1);

	//vertex 
	//g.topoSort_dfs();
	g.topoSortAll();

	getchar();
	return 0;
}