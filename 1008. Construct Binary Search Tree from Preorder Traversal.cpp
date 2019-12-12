//Runtime: 4 ms, faster than 83.62% of C++ online submissions for Construct Binary Search Tree from Preorder Traversal.
//Memory Usage: 8.9 MB, less than 100.00% of C++ online submissions for Construct Binary Search Tree from Preorder Traversal.

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
    
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        if(preorder.size() == 0) return NULL;
        TreeNode *root, *pre, *cur;
        root = new TreeNode(preorder[0]);
        
        for(int i = 1; i < preorder.size(); i++){
            int p = preorder[i];
            cur = root;
            while(cur){
                pre = cur;
                if(p < cur->val){
                    cur = cur->left;
                }else if(p >= cur->val){
                    cur = cur->right;
                }
            }
            if(p < pre->val){
                pre->left = new TreeNode(p);
            }else if(p >= pre->val){
                pre->right = new TreeNode(p);
            }
        }
        return root;
    }
};
