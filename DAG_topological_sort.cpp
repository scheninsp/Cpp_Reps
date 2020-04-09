//toposort
//output:
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

	//indegree
	vector<int> indegree;

public:

	Graph(int n) :nv(n) { 
		adj = new list<int>[nv]; 
	
		for (int i = 0; i < nv; i++)
			indegree.push_back(0);
	};

	~Graph() {
		delete[] adj;
	}

	void addEdge(int v, int w) {
		adj[v].push_back(w);

		indegree[w]++;
	}


	//topological sort
	// a vertex u precedes v if all directed edge uv has u->v
	// return all possibilities of toposort
	void topoSortAllUtil(vector<int>& res, bool visited[]) {
		
		bool flag = false;

		for (int i = 0; i < nv; i++) {
			
			//find a vertex without preceder
			if (indegree[i] == 0 && !visited[i]) {

				list<int>::iterator j;
				for (j = adj[i].begin(); j != adj[i].end(); j++) {
					indegree[*j]--;
				}

				res.push_back(i);
				visited[i] = true;
				topoSortAllUtil(res, visited);

				//reset all states(res, visited, indegree)
				visited[i] = false;
				res.erase(res.end()-1);
				for (j = adj[i].begin(); j != adj[i].end(); j++) {
					indegree[*j]++;
				}

				flag = true;
			}

		}

		if (!flag) {
			for (unsigned int i = 0; i < res.size(); i++)
				cout << res[i] << " ";
			cout << endl;
		}

	}

	void topoSortAll() {
		
		bool *visited = new bool[nv];
		for (int i = 0; i < nv; i++) {
			visited[i] = false;
		}

		vector<int> res;
		topoSortAllUtil(res, visited);
	}

};

int main2() {
	Graph g(6);
	g.addEdge(5,2);
	g.addEdge(5,0);
	g.addEdge(4,0);
	g.addEdge(4,1);
	g.addEdge(2,3);
	g.addEdge(3,1);

	//vertex 
	g.topoSortAll();

	getchar();
	return 0;
}