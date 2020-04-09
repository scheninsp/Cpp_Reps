//generate full permutation of a set

#include <unordered_set>
#include <vector>
#include<iostream>

using std::unordered_set;
using std::vector;
using std::cout;
using std::endl;

void print_full_permutation_util(bool* visited, unordered_set<int> &set, vector<int> res) {

	bool isAll = false;

	int cnt = 0;
	for (unordered_set<int>::iterator it = set.begin(); it != set.end(); it++) {
		if (!visited[cnt]) {
			res.push_back(*it);
			visited[cnt] = true;
			print_full_permutation_util(visited, set, res);
			res.pop_back();
			visited[cnt] = false;

			isAll = true;
		}
		cnt++;
	}

	if(!isAll){
		for (vector<int>::iterator it = res.begin(); it != res.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}


}

void print_full_permutation(unordered_set<int> &set) {

	bool* visited = new bool[set.size()];
	int cnt = 0;
	for (unordered_set<int>::iterator it = set.begin(); it != set.end(); it++) {
		visited[cnt] = false;
		cnt++;
	}

	vector<int> res;
	print_full_permutation_util(visited, set, res);

	delete[] visited;

};

int main() {

	unordered_set<int> set;
	set.insert(1);
	set.insert(2);
	set.insert(3);
	set.insert(4);

	print_full_permutation(set);

	getchar();
	return 0;
}