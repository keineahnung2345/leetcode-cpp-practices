//https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/discuss/274610/JavaC%2B%2BPython-Top-Down

//Top Down
//Runtime: 4 ms, faster than 96.94% of C++ online submissions for Maximum Difference Between Node and Ancestor.
//Memory Usage: 11.9 MB, less than 86.36% of C++ online submissions for Maximum Difference Between Node and Ancestor.

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
    int maxAncestorDiffMM(TreeNode* node, int mx, int mn){
        return node ? max(maxAncestorDiffMM(node->left, max(node->val, mx), min(node->val, mn)),
                    maxAncestorDiffMM(node->right, max(node->val, mx), min(node->val, mn))): mx-mn;
    }
    
    int maxAncestorDiff(TreeNode* root) {
        return maxAncestorDiffMM(root, 0, INT_MAX);
    }
};
