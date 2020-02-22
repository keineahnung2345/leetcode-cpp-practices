//Runtime: 24 ms, faster than 51.99% of C++ online submissions for Binary Tree Tilt.
//Memory Usage: 21.8 MB, less than 100.00% of C++ online submissions for Binary Tree Tilt.
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int treeSum(TreeNode* root){
        if(!root) return 0;
        return root->val + treeSum(root->left) + treeSum(root->right);
    }
    
    int findTilt(TreeNode* root) {
        if(!root) return 0;
        return abs(treeSum(root->left) - treeSum(root->right)) + \
            findTilt(root->left) + findTilt(root->right);
    }
};
