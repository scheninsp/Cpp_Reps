//dijkstra
//exp. input
/*
0, 4, 0, 0, 0, 0, 0, 8, 0
4, 0, 8, 0, 0, 0, 0, 11, 0
0, 8, 0, 7, 0, 4, 0, 0, 2
0, 0, 7, 0, 9, 14, 0, 0, 0
0, 0, 0, 9, 0, 10, 0, 0, 0
0, 0, 4, 14, 10, 0, 2, 0, 0
0, 0, 0, 0, 0, 2, 0, 1, 6
8, 11, 0, 0, 0, 0, 1, 0, 7
0, 0, 2, 0, 0, 0, 6, 7, 0
*/
//exp. output
// dist from 0
// 0 4 12 19 21 11 9 8 14
// dist from 1
// 4 0 8 15 22 12 12 11 10

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<list>
#include<fstream>
#include<string.h>
#include<cassert>

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

	void setMatFromFile(std::string filename) {
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

	void dijkstra(int* dp, int v) {
		bool* visited = new bool[nv];
		memset(visited, false, nv * sizeof(bool));

		//dp[i] is all visited nodes shortest path to i
		dp[v] = 0;
		//visited[v] = true; //first loop must set visited[v] = true

		for (int i = 0; i < nv-1; i++) {

			int u = v;
			int shortest = INT_MAX;

			for (int j = 0; j < nv; j++) {
				if (!visited[j] && dp[j] < shortest) {
					u = j;
					shortest = dp[j];
				}
			}
			if (i == 0) { assert(u == v); }
			visited[u] = true;

			for (int j = 0; j < nv; j++) {
				if (!visited[j] && dp[u]!=INT_MAX && mat[u][j] > 0 && dp[u] + mat[u][j] < dp[j]) {
					dp[j] = dp[u] + mat[u][j];
				}
			}

		}

		delete[] visited;

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

	int vst = 1;

	graph.dijkstra(dist, vst);

	std::cout << "dist from " << vst << std::endl;
	for (int i = 0; i < n; i++) {
		std::cout << dist[i] << " ";
	}
	std::cout << std::endl;

	getchar();
	return 0;
}
