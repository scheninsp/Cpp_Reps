//leetcode 347
/*
给定一个非空的整数数组，返回其中出现频率前 k 高的元素。
exp.
input:
nums = [1, 1, 1, 2, 2, 3], k = 2
output:
[1, 2]
*/

#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
	vector<int> topKFrequent(vector<int>& nums, int k) {

		unordered_map<int, int> num_freq;
		//num_freq : <elem, freq>

		for (unsigned int i = 0; i < nums.size(); i++) {
			if (num_freq.find(nums[i]) == num_freq.end()) {
				num_freq.insert(make_pair(nums[i], 1));
			}
			else {
				num_freq[nums[i]]++;
			}
		}

		//using priority queue to implement top k heap, minimum heap
		//pq : <freq, elem>
		//priority_queue <Type, Container, Functional>
		priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > pq;

		for (unordered_map<int, int>::iterator iter = num_freq.begin(); iter != num_freq.end(); iter++) {
			if (pq.size() == k) {
				if (iter->second > pq.top().first) {
					pq.pop();
					pq.push(make_pair(iter->second, iter->first));
				}
			}
			else {
				pq.push(make_pair(iter->second, iter->first));
			}
		}

		vector<int> result;
		//for (auto iter = pq.begin(); iter != pq.end(); iter++) {} //no begin()
		while (!pq.empty()) {
			result.push_back(pq.top().second);
			pq.pop();
		}

		return result;
	}
};


int main() {

	vector<int> nums({ 1,1,1,2,2,3 });
	int k = 2;

	Solution sol;
	vector<int> result = sol.topKFrequent(nums, k);
	for (unsigned int i = 0; i < result.size(); i++) {
		cout << result[i] << " ";
	}
	cout << endl;

	getchar();
	return 0;
}