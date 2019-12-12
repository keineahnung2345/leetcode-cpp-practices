//Runtime: 4 ms, faster than 63.25% of C++ online submissions for Binary Search Tree to Greater Sum Tree.
//Memory Usage: 9.1 MB, less than 100.00% of C++ online submissions for Binary Search Tree to Greater Sum Tree.

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
    int acc = 0;
    void inOrder(TreeNode* node){
        //in-order traversal, from right to left
        
        //visit right child
        if(node->right) inOrder(node->right);
        
        //visit itself
        node->val += acc;
        //acc becomes old node->val + acc
        acc = node->val;
        
        //visit left child
        if(node->left) inOrder(node->left);
    };
    
    TreeNode* bstToGst(TreeNode* root) {
        if(root) inOrder(root);
        return root;
    }
};
