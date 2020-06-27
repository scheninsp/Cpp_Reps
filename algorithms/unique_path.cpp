//m*n grid, walking from topleft to bottomright
//step allowed only right or down
//return path number

class Solution {
public:
    int uniquePaths(int m, int n) {
        int nGrid=m+n-2;
        int minLen=m<n?m-1:n-1;

        int ans = 1;
        for(int i=1; i<=minLen; i++)
            ans=ans*(nGrid-i+1)/i;
		
        return ans;
    }
};
