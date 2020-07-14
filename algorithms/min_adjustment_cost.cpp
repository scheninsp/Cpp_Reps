class Solution {
public:
    int MinAdjustmentCost(vector<int> &arr, int target) {
       
       if(arr.size() == 1 || arr.size() == 0)
	   {
			return 0;
       }
       
       int** m = new int* [arr.size()];
       for(int i = 0 ; i < arr.size() ; i++)
       {
			m[i] = new int[100]; 
       }
       
       for(int i = 0 ; i < 100 ;i ++)
       {
            m[0][i] = abs(i-arr.at(0));    
       } 
       
       int min;
       int min_adj; 
       for(int i = 1 ; i < arr.size() ;i++)
       {
		   min_adj = 100000;
		   for(int j = 0 ; j < 100 ; j++)
		   {
			   min = 100000;
			   for(int k = -target ; k < target+1 ; k++)
			   {
				   if(k+j < 0 || k+j >= 100)
				   {
					   continue;
				   }
				if(min > m[i-1][k+j] + abs(j-arr.at(i)))
				   {
					   min = m[i-1][k+j] + abs(j-arr.at(i));      
				}
			   }
			   m[i][j] = min;
			   
				if(m[i][j] < min_adj)
			   {
				   min_adj = m[i][j];    
			   }
			} 
        } 
        
       return min_adj;
    }
};