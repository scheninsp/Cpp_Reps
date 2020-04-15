//binary palindrome 
//palindrome must start with 1 and has maximum number of 0
//exp.
//input:
//n=5, k=3
//output: 11011
//n=10, k=4
//output: 1100110011
//n=2, k=8
//output: 11

#include <iostream> 
#include <vector> 
using namespace std; 
  
void dfs(int parent, int ans[], vector<int> str[]) 
{ 
    ans[parent] = 1; 
  
    for (int i = 0; i < str[parent].size(); i++) { 
        if (!ans[str[parent][i]]) 
            dfs(str[parent][i], ans, str); 
    } 
} 
  
void binary_palindrome(int n, int k) 
{ 
    int arr[n], ans[n] = { 0 }; 
  
    vector<int> str[k]; 
  
    for (int i = 0; i < n; i++) 
        arr[i] = i % k; 
  
  for (int i = 0; i < n / 2; i++) { 
        str[arr[i]].push_back(arr[n - i - 1]); 
        str[arr[n - i - 1]].push_back(arr[i]); 
    } 
  
    dfs(0, ans, str); 
  
    for (int i = 0; i < n; i++) 
        cout << ans[arr[i]]; 
} 
  
int main() 
{ 
    int n = 10, k = 4; 
    binary_palindrome(n, k); 
	
	getchar();
    return 0; 
} 