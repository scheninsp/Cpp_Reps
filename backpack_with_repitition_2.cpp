//perfect sum

/*
Example:

nums = [1, 2, 3]
target = 4

The possible combination ways are :
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
*/

#include<vector>
#include<iostream>

using std::vector;
using std::cout;
using std::endl;

//print 2d dp table
static void print2d(bool** const dp, int imax, int jmax) {
	for (int i = 0; i < imax; i++) {
		for (int j = 0; j < jmax; j++) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
}

void perfect_sum_util(bool** dp, int last, int* nums, int len, int target, vector<int> result) {
	if (dp[last][target]) { //there is still possibility
		
		if (last > 0) {
			for (int k = 0; k*nums[last] <= target; k++) {
				if (dp[last - 1][target - k * nums[last]]) {//there is still possibility
					result.push_back(k);
					perfect_sum_util(dp, last - 1, nums, len, target - k * nums[last], result);
					result.pop_back();
				}
			}
		}
		else {  //reach endpoint at dp[0][x]
			int k = target / nums[last];
			result.push_back(k);
			for (int i = result.size() - 1; i >= 0; i--) {
				cout << result[i] << " ";
			}
			cout << endl;
			result.pop_back();
			//traceback to next k
		}
	}
};


void perfect_sum(int* nums, int len, int target) {

	bool **dp = new bool *[len];
	for (int i = 0; i < len; i++) {
		dp[i] = new bool[target+1];  //endpoint, reach nums[0]
	}
	
	//build dp
	for (int i = 0; i < target+1; i++) {
		dp[0][i] = (i % nums[0]) == 0;
	}
	for (int i = 0; i < len; i++) {
		dp[i][0] = true;   //endpoint, target remains 0
	}
	//backtrack
	for (int i = 1; i < len; i++) {
		for (int j = 1; j < target+1; j++) {
			dp[i][j] = false;
			int k = 0;
			while ( k*nums[i] <= j) {
				dp[i][j] = dp[i][j] || dp[i - 1][ j - k*nums[i] ];  //find T as a way, if all false , no result
				k++;
			}
		}
	}

	print2d(dp, len, target + 1);
	
	//find results
	vector<int> result;
	perfect_sum_util(dp, len-1, nums, len, target, result);

	for (int i = 0; i < len; i++) {
		delete[] dp[i];
	}
	delete[] dp;
};



int main() {

	const int LEN = 3;

	int nums[LEN] = {3, 2, 1 };

	int target = 4;

	perfect_sum(nums, LEN, target);

	getchar();
	return 0;
}