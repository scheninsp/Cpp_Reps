/*
leetcode.31 实现获取下一个排列的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。

exp.
1,2,3 -> 1,3,2
*/

//this solution is not well at memory and time cost

#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
	void nextPermutation(vector<int>& nums) {

		int n = nums.size();

		if (n == 1 || n == 0) {
			return;
		}

		int p = -1;

		//find first non decreasing element from back
		//exp. 1 (2) 5 4 3
		for (unsigned int i = n - 1; i > 0; i--) {
			if (nums[i - 1] < nums[i]) {
				p = i - 1;
				break;
			}
		}
		//if already max in dictionary order, return 1st
		if (p == -1) {
			reverse(nums, 0, n-1);
			return;
		}

		//swap first nondecreasing element with first(from back) > nums[p] element 
		//exp. 1 (3) 5 4 2
		int k = p + 1;
		for (unsigned int i = n - 1; i > 0; i--) {
			if (nums[i] > nums[p]) {
				k = i;
				break;
			}
		}
		int tmp = nums[p];
		nums[p] = nums[k];
		nums[k] = tmp;

		//reverse sequence after first non decreasing position
		reverse(nums, p+1, n-1);

	}

	void reverse(vector<int> &nums, unsigned int left, unsigned int right) {
		int tmp = 0;  //faster than inside
		while (left < right) {
			tmp = nums[left];
			nums[left] = nums[right];
			nums[right] = tmp;
			left++;
			right--;
		}
	}

	void print1d(vector<int> &nums) {
		for (auto iter = nums.begin(); iter != nums.end(); iter++) {
			cout << *iter << " ";
		}
		cout << endl;
	}
};



int main() {

	vector<int> nums = { 3,2,5,1,4 };
	
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