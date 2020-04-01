//given a 0-1 matrix, 0 for water, output number of all islands

/*
input:
11000
11000
00100
00011
00011
output:3
*/

#include "islands.h"

using namespace std;

int main() {
	string filename("input.txt");
	shared_ptr<Matrix<int>> pmat = readMatrix<int>(filename);

	pmat->print();

	getchar();
	return 0;
}