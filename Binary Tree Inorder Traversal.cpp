//https://leetcode.com/problems/binary-tree-postorder-traversal/discuss/45551/Preorder-Inorder-and-Postorder-Iteratively-Summarization/188240
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        if(!root) return ans;
        
        stack<TreeNode*> stk;
        
        TreeNode* cur = root;
        
        while(cur || !stk.empty()){
            while(cur){
                stk.push(cur);
                cur = cur->left;
            }
            cur = stk.top(); stk.pop();
            ans.push_back(cur->val);
            
            cur = cur->right;
        }
        
        return ans;
    }
};
