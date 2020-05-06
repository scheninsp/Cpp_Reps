//exp.
//abca
//output:3

#include<string>
#include<iostream>
#include<vector>  
using namespace std;

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		if (s.size() == 0) {
			return 0;
		}

		vector<int> m_map(128, -1); //use a fixed_length vector as hashmap with 128 character set

		unsigned int max_len = 0;
		unsigned int m_len = 0;
		int barrier = 0;   //after meet same character, all i < barrier are seen as removed from hashmap

		for (unsigned int i = 0; i < s.size(); i++) {
			if (m_map[static_cast<int>(s[i])] < barrier) {
				m_map[static_cast<int>(s[i])] = i;
				m_len++;
			}
			else {
				//roll back from next to same char
				if (m_len > max_len) { max_len = m_len; }
				barrier = m_map[static_cast<int>(s[i])];
				m_len = i - m_map[static_cast<int>(s[i])];
				m_map[static_cast<int>(s[i])] = i;
			}
		}

		if (m_len > max_len) { max_len = m_len; }
		return max_len;
	}
};

int main() {

	string s = "dvdf";

	Solution sol;
	cout << s << endl;
	cout << "max length : " << sol.lengthOfLongestSubstring(s) << endl;

	getchar();
	return 0;

}