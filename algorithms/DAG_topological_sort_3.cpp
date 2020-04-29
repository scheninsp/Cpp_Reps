//toposort
// topoSort_dfs output:
//4 5 0 2 3 1 

// topoSortAll output:
//4 5 0 2 3 1 
//4 5 2 0 3 1
//...
//5 4 2 3 0 1
//5 4 2 3 1 0

// add loop detection

#include<iostream>
#include<vector>
#include<string.h>
#include<cassert>

using namespace std;

class DAGraph {

public:
	int nv;
	vector<int*> adj;
	int* indegree;

	DAGraph(int n):nv(n) {
		for (int i = 0; i < nv; i++) {
			int* row = new int[nv];
			memset(row, 0, nv * sizeof(int));
			adj.push_back(row);
		}
		indegree = new int[nv];
		memset(indegree, 0, nv * sizeof(int));

	};

	~DAGraph() {
		for (int i = 0; i < nv; i++) {
			delete adj[i];
		}
		delete indegree;
	}

	void add_edge(int v, int w) {
		adj[v][w] = 1;
		indegree[w] ++;
	}

	void has_loop_util(int* visited, int v, bool &flag) {
		//dfs
		//cout << "visit" << v << endl;
		if (visited[v] == 2) {
			flag = true;
		}
		else if (visited[v] == 0) {
			visited[v] = 2;
			for (int i = 0; i < nv; i++) {
				if (adj[v][i] > 0 && visited[i] != 1) {
					has_loop_util(visited, i, flag);
				}
			}
			visited[v] = 1;
		}
	}

	bool has_loop() {
		int* visited = new int[nv];
		memset(visited, 0, nv * sizeof(int));

		//visited = 1 (visited), 0(unvisited), 2(visiting)
		bool flag = false;
		for (int i = 0; i < nv; i++) {
			has_loop_util(visited, i, flag);
			if(flag) { break; }
			memset(visited, 0, nv * sizeof(int));  //reset for next start point 
		}

		return flag;
	}

	void topo_sort_all_rec(bool* visited, vector<int> &res) {

		bool flag = false;

		for (int i = 0; i < nv; i++) {
			if (indegree[i] == 0 && !visited[i]) {
				flag = true; //still has unvisited nodes

				res.push_back(i);
				for (int j = 0; j < nv; j++) {
					if (adj[i][j] >0) {
						indegree[j]--;
					}
				}

				visited[i] = true;
				topo_sort_all_rec(visited, res);

				assert(res.back() == i);
				res.pop_back();  
				for (int j = 0; j < nv; j++) {
					if (adj[i][j] >0) {
						indegree[j]++;
					}
				}
				visited[i] = false;

			}
		}

		if (!flag) {  //return with all visited 
		for (int i = 0; i <nv; i++) {
				cout << res[i] << " ";
			}
			cout << endl;
		}


	}

	void topo_sort_all() {

		vector<int> res;
		bool* visited = new bool[nv];
		memset(visited, false, nv * sizeof(bool));

		topo_sort_all_rec(visited, res);

		delete visited;

	}
};


int main() {

	DAGraph g(6);
	g.add_edge(5, 2);
	g.add_edge(5, 0);
	g.add_edge(4, 0);
	g.add_edge(4, 1);
	g.add_edge(2, 3);
	g.add_edge(3, 1);
	g.add_edge(1, 2);  //loop

	cout << "Loop:" << g.has_loop() << endl;
	
	if (!g.has_loop()) {
		g.topo_sort_all();
	}

	getchar();
	return 0;

}