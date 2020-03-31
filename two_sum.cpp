//two sum leetcode

//exp.
//nums = [2,7,11,15]
//target = 9

//three sum


#include<vector>
#include<unordered_map>
#include<iostream>

using namespace std;

vector<int> twoSum(vector<int> &nums, int target) {
	unordered_map<int, int> hash;
	vector<int> result;

	for (int i = 0; i < nums.size(); i++) {
		hash.insert(pair<int,int>(nums[i],nums[i]));
	}

	for (int i = 0; i < nums.size(); i++) {
		int rem = target - nums[i];
		if (hash.find(rem) != hash.end()) {
			result.push_back(hash[rem]);
			result.push_back(i);
		}
	}
	return result;
}

int main() {
	
	const int LEN = 4;
	int a[LEN] = { 2,7,11,15 };
	vector<int> array(a, a+LEN);

	vector<int> result = twoSum(array, 9);

	vector<int>::iterator i;
	for (i = result.begin(); i != result.end(); i++) {
		cout << *i << " ";
	}

	cout << endl;
	getchar();
	return 0;
}
