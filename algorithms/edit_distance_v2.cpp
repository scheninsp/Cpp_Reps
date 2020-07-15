#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int edit_dist(string str1, string str2)
{
	int len1 = str1.size();
	int len2 = str2.size();

	vector<vector<int>> dp( len1+1, vector<int>( len2+1, 0) );

	dp[0][0] = 0;
	
	//initialize
	for (i=1;i<=len1;++i)
	{
		dp[i][0] = i;
	}
	
	for (i=1;i<=len2;++i)
	{
		dp[0][i] = i;
	}
	
	//progress
	for (i=1;i<=len1;++i)
	{
		for (j=1;j<=len2;++j)
		{
			if (str1[i-1]==str2[j-1])
			{
				dp[i][j] = dp[i - 1][j - 1];
			}
			else
			{
				dp[i][j] = min(dp[i][j - 1], min(dp[i - 1][j - 1], dp[i - 1][j]))+1;
			}
		}
	}
	
	return dp[len1][len2];
	
}

int main()
{
	string str1;
	string str2;
	
	while ( cin >> str1 >> str2 )
	{
		cout << edit_dist(str1, str2) << endl;
		str1.clear();
		str2.clear();
	}
	
	getchar();
	return 0;
}