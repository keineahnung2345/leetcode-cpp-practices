//Runtime: 28 ms, faster than 34.86% of C++ online submissions for House Robber III.
//Memory Usage: 25.1 MB, less than 16.67% of C++ online submissions for House Robber III.
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
class Solution {
public:
    unordered_map<TreeNode*, int> memo;
    
    int rob(TreeNode* root) {
        if(root == nullptr) return 0;
        if(memo.find(root) != memo.end()) return memo[root];
        
        int robHere = root->val;
        if(root->left) robHere += rob(root->left->left) + rob(root->left->right);
        if(root->right) robHere += rob(root->right->left) + rob(root->right->right);
        
        int robNext = rob(root->left) + rob(root->right);
        
        memo[root] = max(robHere, robNext);
        return memo[root];
    }
};
