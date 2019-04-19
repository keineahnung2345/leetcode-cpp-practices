//Runtime: 16 ms, faster than 99.38% of C++ online submissions for Minimum Depth of Binary Tree.
//Memory Usage: 20.1 MB, less than 7.64% of C++ online submissions for Minimum Depth of Binary Tree.

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
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        if(root->left && root->right)return 1 + min(minDepth(root->left), minDepth(root->right));
        //if only one side is not null, we calculate depth using that side
        return 1 + max(minDepth(root->left), minDepth(root->right));
    }
};
