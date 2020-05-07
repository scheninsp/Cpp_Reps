//leetcode.49 给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。
//exp.
//input
/*
输入: ["eat", "tea", "tan", "ate", "nat", "bat"]
输出:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]

exp. input file: 
eat,tea,tan,ate,nat,bat
shit,isht,bnfhwv,sjhcn,shiit,ihst
zdb,wubeb,suzd,hur,dbz,ruh
*/

#define _CRT_SECURE_NO_WARNINGS 

#include<iostream>
#include<unordered_map>
#include<string>
#include<fstream>

#define NALPHABET 26
#define MAX_STRING_LENGTH 2048

using namespace std;

class Solution {
private:

public:
	//define a hashcode with number of 26 alphabets
	string hashfunc(string s) {

		int nums[NALPHABET] = { 0 };

		for (unsigned int i = 0; i < s.size(); i++) {
			unsigned int ipos = static_cast<int>(s[i]) - static_cast<int>('a');
			if ( ipos < NALPHABET) {
				nums[ipos]++;
			}
			else {
				memset(nums, 0, sizeof(int)*NALPHABET);
				break;
			}
		}

		string code = "";
		for (int i = 0; i < NALPHABET; i++) {
			char tmp[MAX_STRING_LENGTH];
			sprintf(tmp, "%d", nums[i]);
			unsigned int nchar = 1;
			int rem = nums[i];
			while (rem / 10 != 0) {
				nchar++;
				rem = rem / 10;
			}
			code.append(string(tmp, nchar));
			code.append("#");
		}

		return code;
	}

	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<vector<string>> answers;

		unordered_map<string, unsigned int> m_map;

		unsigned int endpos = 0;
		for (unsigned int i = 0; i < strs.size(); i++) {
			string code = hashfunc(strs[i]);
			if (m_map.find(code) == m_map.end()) {
				vector<string> tmp;
				tmp.push_back(strs[i]);
				answers.push_back(tmp);
				m_map.insert(make_pair(code, endpos));
				endpos++;
			}
			else {
				unsigned int insert_pos = m_map[code];
				answers[insert_pos].push_back(strs[i]);
			}
		}
		return answers;
	}
};

static void read_strs_from_file(vector<vector<string>> &vector_of_strs, string filename) {
	ifstream ifs(filename);
	if (!ifs) {
		return;
	}
	
	const int MAXLINE = 1024;
	char* tmp;
	char buf[MAXLINE] = { 0 };

	while (ifs.getline(buf, MAXLINE)) {
		vector<string> one_row;
		tmp = strtok(buf, ",");
		while (tmp) {
			int nchar = 0;
			while (tmp[nchar] != '\0') {
				nchar++;
			}
			one_row.push_back(string(tmp, nchar));
			tmp = strtok(NULL, ",");
		}
		vector_of_strs.push_back(one_row);
	}

}

int main() {

	vector<vector<string>> vector_of_strs;

	read_strs_from_file(vector_of_strs, "input.txt");


	for (unsigned int iTask = 0; iTask < vector_of_strs.size(); iTask++) {
		vector<string> strs = vector_of_strs[iTask];
		cout << "Task " << iTask << ": ";
		for (unsigned int j = 0; j < strs.size(); j++) {
			cout << strs[j] << ", ";
		}
		cout << endl;

		Solution sol;
		vector<vector<string>> answers = sol.groupAnagrams(strs);

		for (unsigned int i = 0; i < answers.size(); i++) {
			for (unsigned int j = 0; j < answers[i].size(); j++) {
				cout << answers[i][j] << ", ";
			}
			cout << endl;
		}
	}

	getchar();
	return 0;

}