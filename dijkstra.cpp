#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<list>
#include<fstream>

static void readFile(std::string filename, int** mat, int n) {

	std::ifstream ifs = std::ifstream(filename);

	const int maxLine = 256;
	char buf[maxLine] = { 0 };
	char* tmp;
	int cnt_row = 0;

	while (ifs.getline(buf, maxLine) && cnt_row < n) {
		int cnt_col = 0;
		tmp = strtok(buf, " ");
		while (tmp && cnt_col < n) {
			int num = atoi(tmp);
			tmp = strtok(NULL, " ");

			mat[cnt_row][cnt_col] = num;
			cnt_col++;
		}
		cnt_row++;
	}

}

class Graph {
private:
	int nv;
	int** mat;

public:

	Graph() = delete;

	Graph(int n) :nv(n) {
		mat = new int*[n];
		for (int i = 0; i < n; i++) {
			mat[i] = new int[n];
		}
	};

	~Graph() {
		for (int i = 0; i < nv; i++) {
			delete mat[i];
		}
		delete mat;
	};

	void setMatFromFile(std::string filename){
		readFile(filename, mat, nv);
	};

	void printMat() {
		for (int i = 0; i < nv; i++) {
			for (int j = 0; j < nv; j++) {
				std::cout << mat[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	void dijkstra(int* dist, int v) {

		bool* visited = new  bool[nv];
		for (int i = 0; i < nv; i++) {
			visited[i] = false;
		}

		dist[v] = 0;

		for (int i = 0; i < nv - 1; i++) {  //visit nv-1 vertex will finish 

			//get a unprocessed vertex with current shortest path to v
			int shortest = INT_MAX;
			int  u = 0;
			for (int i = 0; i < nv; i++) {
				if (visited[i] == false && dist[i] < shortest) {
					u = i;
					shortest = dist[i];
				}
			}
			visited[u] = true;

			//update dist
			for (int j = 0; j < nv; j++) {
				//dist[u]!=INT_MAX to avoid cross limit
				if (!visited[j] && mat[u][j] && dist[u] != INT_MAX && dist[u] + mat[u][j] < dist[j]) {
					dist[j] = dist[u] + mat[u][j];
				}
			}

		}

		delete visited;
	}

};



int main() {

	int n = 9;

	Graph graph(n);

	graph.setMatFromFile("input.txt");
	graph.printMat();

	int* dist = new int[n];
	for (int i = 0; i < n; i++) {
		dist[i] = INT_MAX;
	}

	int vst = 0;

	graph.dijkstra(dist, vst);

	std::cout << "dist from " << vst << std::endl ;
	for (int i = 0; i < n; i++) {
		std::cout << dist[i] << " ";
	}
	std::cout << std::endl;

	getchar();
	return 0;
}
