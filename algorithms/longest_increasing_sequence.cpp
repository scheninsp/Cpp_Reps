//longest increasing subsequence

class Solution {
public:

    int longestIncreasingSubsequence(vector<int> &arr) {
       int * m = new int [arr.size()];
       int ans = 0 ;
       
       m[0] = 1;
       
       
       for(int i = 1 ; i < arr.size();i++)
       {
               m[i] = 1;
               for(int j = 0 ; j < i ; j++)
               {
                   if(arr.at(i) > arr.at(j))
                {
                    if(m[i] < m[j] + 1 )
                        m[i] = m[j] + 1;           
                }    
            }
            if(ans < m[i])
            {
                ans = m[i];
            }
       } 
       return ans ;
    }
};
