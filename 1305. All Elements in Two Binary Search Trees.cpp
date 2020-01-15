//Runtime: 280 ms, faster than 58.55% of C++ online submissions for All Elements in Two Binary Search Trees.
//Memory Usage: 58.1 MB, less than 100.00% of C++ online submissions for All Elements in Two Binary Search Trees.

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
    
    void dfs(TreeNode* root){
        stack<TreeNode*> stk;
        TreeNode *node;
        
        stk.push(root);
        while(!stk.empty()){
            node = stk.top(); stk.pop();
            if(!node) return;
            ans.push_back(node->val);
            if(node->left){
                stk.push(node->left);
            }
            if(node->right){
                stk.push(node->right);
            }
        }
    }
    
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        dfs(root1);
        dfs(root2);
        sort(ans.begin(), ans.end());
        return ans;
    }
};
