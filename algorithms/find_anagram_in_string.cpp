/*
leetcode.348 给定一个字符串和一个非空字符串,找到中所有是的字母异位词的子串,返回这些子串的起始索引

exp. 
input:
s: "cbaebabacd" p : "abc"
output:
[0, 6]
*/

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Solution {
public:

	static const int NALPHABET = 26;
	static const int MAX_STRING_LENGTH = 20100;

	void hashfunc(int* nums, string::iterator iter, unsigned int length) {

		//int nums[NALPHABET] = { 0 };

		for (unsigned int i = 0; i < length; i++) {
			if (static_cast<int>(*iter) - static_cast<int>('a') < NALPHABET)
			{
				nums[static_cast<int>(*iter) - static_cast<int>('a')]++;
			}
			iter++;
		}
	};

	void update_hashfunc(int* nums, string::iterator iter, unsigned int length) {
		//update nums from [iter, iter+length-1] to [iter+1, iter+length]
		if (static_cast<int>(*iter) - static_cast<int>('a') < NALPHABET)
		{
			nums[static_cast<int>(*iter) - static_cast<int>('a')]--;
		}

		iter += length;
		if (static_cast<int>(*iter) - static_cast<int>('a') < NALPHABET)
		{
			nums[static_cast<int>(*iter) - static_cast<int>('a')]++;
		}
	}

	vector<int> findAnagrams(string s, string p) {
		
		vector<int> answer;

		if (p.size() > s.size()) {
			return answer;
		}

		int target_hash[NALPHABET] = { 0 };
		hashfunc(target_hash, p.begin(), p.size());

		int sliding_hash[NALPHABET] = { 0 };
		string::iterator left = s.begin();
		int count = 0;
		//1st hashcode
		hashfunc(sliding_hash, left, p.size());
		if (!memcmp(sliding_hash, target_hash, NALPHABET * sizeof(int))) {
			answer.push_back(count);
		}
		count++;

		//update sliding hashcode
		while (left != s.end() - p.size()) {
			update_hashfunc(sliding_hash, left, p.size());  //[left, left+length-1] -> [left+1, left+length]
			if (!memcmp(sliding_hash, target_hash, NALPHABET*sizeof(int))) {
				answer.push_back(count);
			}
			count++;
			left++;
		}

		return answer;
	}
};


int main() {

	Solution sol;
	string s = "cbaebabacd";
	string p = "abc";

	//string s = "aaaaaaaaaa";
	//string p = "aaaaaaaaaaaaa";

	vector<int> answer = sol.findAnagrams(s, p);

	cout << s << endl;
	cout << p << endl;
	for (unsigned int i = 0; i < answer.size(); i++) {
		cout << answer[i] << " ";
	}
	cout << endl;

	getchar();
	return 0;
}