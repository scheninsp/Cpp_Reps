#define _CRT_SECURE_NO_WARNINGS //for strtok()

#include <iostream>
#include <fstream>
#include <vector>
#include "backpack01.h"

using namespace std;

short readFile(vector<vector<int>> &elements) {
	
	short errorcode = 0;

	ifstream frd("./input.txt");
	const int maxLine = 256;
	char buf[maxLine] = {0};
	char* tmp;

	while (frd.getline(buf, maxLine)) {
		vector<int> one_row;
		tmp = strtok(buf, " ");
		while (tmp) {
			int num = atoi(tmp);
			tmp = strtok(NULL, " ");
			one_row.push_back(num);
		}
		elements.push_back(one_row);
	}

	return errorcode;

};

int main() {
	vector<vector<int>> elements;

	short errorcode = readFile(elements);

	if (!errorcode) {
		for (int i = 0; i < elements.size(); i++) {
			for (int j = 0; j < elements[i].size(); j++) {
				cout << elements[i][j] << " ";
			}
			cout << endl;
		}
	}
	else {
		cout << "read error:" << errorcode << endl;
	}

	getchar();
};