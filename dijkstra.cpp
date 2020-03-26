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

};



int main() {


	Graph graph(9);

	graph.setMatFromFile("input.txt");
	graph.printMat();

	//dijkstra(graph, 0);

	getchar();
	return 0;
}
