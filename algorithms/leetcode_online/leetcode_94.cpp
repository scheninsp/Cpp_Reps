/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include<vector>

class Solution {
public:
    void inorder_util(TreeNode* root, vector<int> &res){
        if(root != nullptr){
            inorder_util(root->left, res);
            res.push_back(root->val);
            inorder_util(root->right, res);
        }
    }

    vector<int> inorderTraversal(TreeNode* root) {

        vector<int> res;
        inorder_util(root, res);
        
        return res;
    };

};