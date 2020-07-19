//leetcode.112
//find path sum in tree
public class Solution {
    
	boolean ans = false;

    public boolean path_sum_in_tree(Node root, int sum) {
        
		if (root == null) {
            return false;
        }
		
        dfs(root, sum);
        return ans;
    }

    void dfs(Node root, int sum) {
		
        if (root == null) {
            return;
        }

        if (sum == root.val && root.left == null && root.right == null) {
            ans = true;
        }

        dfs(root.left, sum - root.val);
        dfs(root.right, sum - root.val);
    }
}