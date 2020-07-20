#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	double find_median(vector<int>& arr1, vector<int>& arr2) {
	
		vector<int> sum;
		int half = sum.size() / 2;
		
		sum.insert(sum.end(), arr1.begin(), arr1.end());
		sum.insert(sum.end(), arr2.begin(), arr2.end());
		
		sort(sum.begin(), sum.end());
		
		double ans = 0;
		if((sum.size() % 2) == 0)
		{
			ans = (sum[half-1] + sum[half]) / 2.0 ;
		}
		else
		{
			ans = (double)sum[half];
		}
		return ans;
	}
	
};