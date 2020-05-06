/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

#include<list>

class Solution {
public:
    void preOrder(TreeNode* root, list<TreeNode*>& list){
        if(root != nullptr){
            list.push_back(root);

            preOrder(root->left, list);
            preOrder(root->right, list);
        }
        else{
            list.push_back(nullptr);
        }
    }

    void flatten(TreeNode* root) {
        list<TreeNode*> l;

        preOrder(root, l);

        for(list<TreeNode*>::iterator it = l.begin(); it!= l.end(); it++){
            if( *it == nullptr ){ cout <<"null,";}
            else{cout<< (*it)->val << ",";}
        }
    }
};