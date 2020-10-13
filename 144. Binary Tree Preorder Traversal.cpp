//Runtime: 4 ms, faster than 50.88% of C++ online submissions for Binary Tree Preorder Traversal.
//Memory Usage: 9 MB, less than 9.54% of C++ online submissions for Binary Tree Preorder Traversal.
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
    vector<int> ans;
    
    void preorder(TreeNode* node){
        if(!node) return;
        ans.push_back(node->val);
        preorder(node->left);
        preorder(node->right);
    }
    
    vector<int> preorderTraversal(TreeNode* root) {
        preorder(root);
        return ans;
    }
};
