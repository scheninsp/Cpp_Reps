/*
leetcode.31 实现获取下一个排列的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。

exp.
1,2,3 -> 1,3,2
*/

//maybe compiler on leetcode has problem, memory cost is strange

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		int len = nums.size();
		if (len == 0) return;

		int i = len - 1;
		while (i >= 0)
		{
			if (!deSorted(nums, i))
			{
				for (int k = len - 1; k > i; k--)
				{
					if (nums[k] > nums[i])
					{
						int temp;
						temp = nums[i];
						nums[i] = nums[k];
						nums[k] = temp;
						break;
					}
				}

				sort(nums.begin() + i + 1, nums.end());
				break;
			}
			i--;
		}
		if (i == -1)
		{
			sort(nums.begin(), nums.end());
		}
	}

	inline bool deSorted(vector<int> nums, int n)
	{

		for (int i = n; i < nums.size(); i++)
		{
			for (int j = i + 1; j < nums.size(); j++)
			{
				if (nums[i] < nums[j])
				{
					cout << "I = false: " << n << endl;
					return false;
				}
			}
		}
		return true;
	}



	void print1d(vector<int> &nums) {
		for (auto iter = nums.begin(); iter != nums.end(); iter++) {
			cout << *iter << " ";
		}
		cout << endl;
	}

};


int main() {

	vector<int> nums = { 5,4,3,2,1 };

	Solution sol;
	sol.print1d(nums);

	sol.nextPermutation(nums);
	cout << "next:" << endl;
	sol.print1d(nums);

	sol.nextPermutation(nums);
	cout << "next:" << endl;
	sol.print1d(nums);

	sol.nextPermutation(nums);
	cout << "next:" << endl;
	sol.print1d(nums);

	getchar();

	return 0;

}