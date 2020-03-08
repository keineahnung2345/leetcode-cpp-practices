//Recursive
//Runtime: 4 ms, faster than 56.80% of C++ online submissions for Binary Tree Inorder Traversal.
//Memory Usage: 9.3 MB, less than 77.00% of C++ online submissions for Binary Tree Inorder Traversal.
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
    vector<int> ans;
    
    void inorderTraversalR(TreeNode* root){
        if(!root) return;
        if(root->left){
            inorderTraversal(root->left);
        }
        ans.push_back(root->val);
        if(root->right){
            inorderTraversal(root->right);
        }
    }
    
    vector<int> inorderTraversal(TreeNode* root) {
        inorderTraversalR(root);
        return ans;
    }
};
