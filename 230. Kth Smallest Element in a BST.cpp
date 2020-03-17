//Runtime: 16 ms, faster than 96.43% of C++ online submissions for Kth Smallest Element in a BST.
//Memory Usage: 20.9 MB, less than 100.00% of C++ online submissions for Kth Smallest Element in a BST.

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
    int k;
    
    int inOrder(TreeNode* node){
        if(!node) return -1;
        int lval = inOrder(node->left);
        if(lval != -1) return lval;
        if(--k == 0){
            return node->val;
        }
        int rval = inOrder(node->right);
        if(rval != -1) return rval;
        return -1;
    };
    
    int kthSmallest(TreeNode* root, int k) {
        this->k = k;
        return inOrder(root);
    }
};
