//longest palindromic string 2

#include<string>
#include<algorithm>
#include<iostream>

using std::string;
using std::min;
using std::cout;
using std::endl;

static int lps_util(int* dp, int len, string& str){
	int p0 = 1;  //rightmost palindromic center
	int p = 2;  //rightmost palindromic length
	dp[0] = 1;
	dp[1] = 2;
	int max_dp_pos = 1;
	int max_dp_len = 2;

	for (int i = 2; i < len; i++) {

		if (i < p0 + p - 1) {
			if (dp[2 * p0 - i] < min(p0 + p - i, i - p0 + 1)) {
				dp[i] = dp[2 * p0 - i];
			}
			else {
				int st = min(p0 + p - i, i - p0 + 1);
				dp[i] = st;
				while (i + st < len - 1 && i - st > 0 ){
					if ((i + st + 1) % 2 == 0) {
						int p1 = (i + st - 1) / 2;
						int p2 = (i - st - 1) / 2;
						if (str[p1] == str[p2]) { dp[i] += 2; }
						else { break; }
					}
					st++;
				}
			}
		}

		else {//i >= p0+p-1
			int st = 0;
			dp[i] = st;
			while (i + st < len - 1 && i - st > 0) {
				if ((i + st + 1) % 2 == 0) {
					int p1 = (i + st - 1) / 2;
					int p2 = (i - st - 1) / 2;
					if (str[p1] == str[p2]) { dp[i] += 2; }
					else { break; }
				}
				st++;
			}
		}

		//reset rightmost 
		if( i + dp[i] - 1 > p0 + p - 1){
			p0 = i;
			p = dp[i];
		}

		if (dp[i] > max_dp_len) {
			max_dp_len = dp[i];
			max_dp_pos = i;
		}
	}

	return max_dp_pos;
};


string lps(string& str) {
	unsigned long const len = str.size() * 2 + 1;
	int* dp = new int[len];
	memset(dp, 0, sizeof(int)*len);

	int max_dp_pos = lps_util(dp, len, str);
	int max_dp_len = dp[max_dp_pos];

	int max_dp_pos_ori = (max_dp_pos - 1) / 2;
	int max_dp_len_ori = (dp[max_dp_pos] + 1) / 2;  //dp[i] does not include last #s
	//print dp
	for (int i = 0; i < len; i++) {
		cout << i << ":" << (dp[i]+1)/2 <<"  "; 
	}
	cout << endl;

	int pbegin = max_dp_pos_ori - max_dp_len_ori + 1;
	int pend = max_dp_pos_ori + max_dp_len_ori - 1;

	string str_p(str, pbegin, pend);

	delete[] dp;
	return str_p;
};

int main() {

	string str = "abcbaaaabcddcba";
	//string str = "abcbaabcddcba";
	//string str = "abcba";

	string x = lps(str);

	cout << x << endl;
	
	getchar();
	return 0;
};