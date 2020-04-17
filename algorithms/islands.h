#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<string>
#include<iostream>
#include<fstream>
#include<memory>

template<typename T>
class Matrix {
private:
	int n;
	T** mat;

public:
	Matrix() :n(0), mat(nullptr) {};

	Matrix(int m) :n(m) {
		mat = new T*[n];
		for (int i = 0; i < n; i++) {
			mat[i] = new T[n];
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				mat[i][j] = 0;
			}
		}
	};

	~Matrix() {
		delete [] mat;
	};

	int size() {
		return n;
	};

	void print() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				std::cout << mat[i][j] << " ";
			}
			std::cout << std::endl;
		}
	};

	template<typename T>
	T& elemAt(int i, int j) {
		return mat[i][j];
	};
};

template<typename T>
static std::shared_ptr<Matrix<T>> readMatrix(std::string filename) {

	std::ifstream ifs(filename);
	const int maxLine = 256;

	char buf[maxLine] = { 0 };
	char* tmp;

	//first line must be 1 number 
	ifs.getline(buf, maxLine);
	int n = atoi(buf);
	std::shared_ptr<Matrix<T>> pmat = std::make_shared<Matrix<T>> (n);

	int row = 0;
	while (ifs.getline(buf, maxLine) && row < n) {
		int col = 0;
		tmp = strtok(buf, ",");
		while (tmp && col < n) {
			T num = static_cast<T>(atoi(tmp));
			tmp = strtok(NULL, ",");
			pmat->elemAt<T>(row, col) = num;
			col++;
		}
		row++;
	}

	return pmat;
};

template<typename T> 
static int findIslands(std::shared_ptr<Matrix<T>> pmat) {
	
	int cntIslands = 0;
	for (int i = 0; i < pmat->size(); i++) {
		for (int j = 0; j < pmat->size(); j++) {
			if (pmat->elemAt<T>(i, j) == 1) {
				cntIslands++;
				dfs_setzero(i, j, pmat);
			}
		}
	}
	return cntIslands;
};

template<typename T>
static void dfs_setzero(int row, int col, std::shared_ptr<Matrix<T>> pmat) {
	if (row+1<pmat->size() && pmat->elemAt<T>(row + 1, col) == 1) {
		row++;
		pmat->elemAt<T>(row, col) = 0;
		dfs_setzero(row, col, pmat);
	}
	if (row-1>=0 && pmat->elemAt<T>(row - 1, col) == 1) {
		row--;
		pmat->elemAt<T>(row, col) = 0;
		dfs_setzero(row, col, pmat);
	}
	if (col + 1 < pmat->size() && pmat->elemAt<T>(row, col+1) == 1) {
		col++;
		pmat->elemAt<T>(row, col) = 0;
		dfs_setzero(row, col, pmat);
	}
	if (col - 1 >= 0 && pmat->elemAt<T>(row, col - 1) == 1) {
		col--;
		pmat->elemAt<T>(row, col) = 0;
		dfs_setzero(row, col, pmat);
	}
	return;
};