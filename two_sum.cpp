//two sum leetcode

//exp.
//nums = [2,7,11,15]
//target = 9

//three sum
//exp.
//nums = [1,4,45,6,10,8}
//target = 22

#include<vector>
#include<unordered_map>
#include<iostream>
#include<unordered_set>
#include<algorithm>
#include<map>  //multimap

using namespace std;

vector<int> twoSum_with_replacement(vector<int> &nums, int target) {
	unordered_map<int,int> hash;
	vector<int> result;

	for (unsigned int i = 0; i < nums.size(); i++) {
		hash.insert(pair<int,int>(nums[i],i));
	}

	for (unsigned int i = 0; i < nums.size(); i++) {
		int rem = target - nums[i];
		if (hash.find(rem) != hash.end()) {
			result.push_back(hash[rem]);
			result.push_back(i);
		}
		hash.erase(nums[i]);
	}
	return result;
}

vector<int> threeSum_with_replacement(vector<int> &nums, int target) {

	unordered_map<int,int> hash;
	vector<int> result;

	for (unsigned int i = 0; i < nums.size(); i++) {
		hash.insert(pair<int, int>(nums[i], i));
	}

	//all replicates are generated (1,2,3)(1,3,2)...(3,2,1)
	for (unsigned int i = 0; i < nums.size(); i++) {
		
		int rem = target - nums[i];
		for (unsigned int j = 0; j < nums.size();j++) {
			if (hash.find(rem - nums[j]) != hash.end()) {
				result.push_back(i);
				result.push_back(j);
				result.push_back(hash[rem - nums[j]]);
			}
		}
	}
	return result;
}

//O(N^2*logN)
vector<int> threeSum_without_replacement(vector<int> &nums, int target) {

	vector<int> result;
	unordered_map<int, int> hash_search;

	for (unsigned int i = 0; i < nums.size(); i++) {
		hash_search.insert(pair<int, int>(nums[i], i));
	}
	for (unsigned int i = 0; i < nums.size(); i++) {

		int rem = target - nums[i];
		unordered_set<int> tmp_set;

		for (unsigned int j = i+1; j < nums.size(); j++) {  //j=i+1 for no replicates
			if (tmp_set.find(rem - nums[j]) != tmp_set.end()) {
				result.push_back(i);
				result.push_back(j);
				result.push_back(hash_search[rem - nums[j]]); //log(n)
			}
			tmp_set.insert(nums[j]);   //this make sure i and j are always not in tmp_set
		}
	}
	return result;
}

//O(N^2), double pointer , interval search
vector<int> threeSum_without_replacement_faster(vector<int> &nums, int target) {

	vector<int> result;

	multimap<int, int> map_nums_indx;
	for (int i = 0; i < nums.size(); i++) {
		map_nums_indx.insert(pair<int, int>(nums[i], i));
	}

	vector<int> map_originalIndx_sortedIndx;
	multimap<int, int>::iterator iter;
	for (iter = map_nums_indx.begin(); iter != map_nums_indx.end(); iter++) {
		map_originalIndx_sortedIndx.push_back(iter->second);
	}
	
	sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size(); i++) {
		int j = i + 1;
		int k = nums.size() - 1;
		while (j < k) {
			if (nums[i] + nums[j] +nums[k] == target) {
				result.push_back(map_originalIndx_sortedIndx[i]);
				result.push_back(map_originalIndx_sortedIndx[j]);
				result.push_back(map_originalIndx_sortedIndx[k]);
				
				j++;
				k--;
			}
			else if (nums[i] + nums[j] + nums[k] < target) {
				j++;
			}
			else if (nums[i] + nums[j] + nums[k] > target) {
				k--;
			}
		}
	}
	return result;
}



int main() {
	
	//two sum
	const int LEN = 4;
	int a[LEN] = { 2,7,11,15 };
	vector<int> array(a, a+LEN);

	vector<int> result = twoSum_with_replacement(array, 9);
	
	cout << "twoSum with replacement: " << endl;
	vector<int>::iterator i;
	for (i = result.begin(); i != result.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;

	//three sum
	const int LEN2 = 6;
	int a2[LEN2] = { 1,4,45,6,10,8 };
	vector<int> array2(a2, a2 + LEN2);
	
	vector<int> result2 = threeSum_with_replacement(array2, 22);
	vector<int> result3 = threeSum_without_replacement(array2, 22);
	vector<int> result4 = threeSum_without_replacement_faster(array2, 22);

	cout << "threeSum with replacement: " << endl;
	vector<int>::iterator i2;
	int cnt = 0;
	for (i2 = result2.begin(); i2 != result2.end(); i2++) {
		cout << *i2 << " ";
		cnt++;
		if (cnt % 3== 0) { cout << " "; }
	}
	cout << endl;

	cout << "threeSum without replacement: " << endl;
	vector<int>::iterator i3;
	int cnt3 = 0;
	for (i3 = result3.begin(); i3 != result3.end(); i3++) {
		cout << *i3 << " ";
		cnt3++;
		if (cnt3 % 3 == 0) { cout << " "; }
	}
	cout << endl;

	cout << "threeSum without replacement faster: " << endl;
	vector<int>::iterator i4;
	int cnt4 = 0;
	for (i4 = result4.begin(); i4 != result4.end(); i4++) {
		cout << *i4 << " ";
		cnt4++;
		if (cnt4 % 3 == 0) { cout << " "; }
	}
	cout << endl;

	getchar();
	return 0;
}
