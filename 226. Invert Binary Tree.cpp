//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Invert Binary Tree.
//Memory Usage: 8.3 MB, less than 100.00% of C++ online submissions for Invert Binary Tree.
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
    TreeNode* invertTree(TreeNode* root) {
        if(root != nullptr){
            swap(root->left, root->right);
            root->left = invertTree(root->left);
            root->right = invertTree(root->right);
        }
        return root;
    }
};
