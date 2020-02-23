//Runtime: 4 ms, faster than 56.08% of C++ online submissions for Second Minimum Node In a Binary Tree.
//Memory Usage: 8.6 MB, less than 64.29% of C++ online submissions for Second Minimum Node In a Binary Tree.

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
    int findSecondMinimumValue(TreeNode* root) {
        stack<TreeNode*> stk;
        TreeNode* cur;
        long min1 = LONG_MAX, min2 = LONG_MAX;
        
        stk.push(root);
        while(!stk.empty()){
            cur = stk.top(); stk.pop();
            if(cur->val < min1){
                min2 = min1;
                min1 = cur->val;
            }else if(cur->val > min1 && cur->val < min2){
                min2 = cur->val;
            }
            
            if(cur->left) stk.push(cur->left);
            if(cur->right) stk.push(cur->right);
        }
        return (min1 == min2) ? -1 : min2;
    }
};
