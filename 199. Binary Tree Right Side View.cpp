//Runtime: 8 ms, faster than 30.77% of C++ online submissions for Binary Tree Right Side View.
//Memory Usage: 12 MB, less than 5.48% of C++ online submissions for Binary Tree Right Side View.
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        if(!root) return ans;
        
        queue<TreeNode*> q;
        
        q.push(root);
        
        while(!q.empty()){
            int level_size = q.size();
            int level_last;
            
            while(level_size--){
                TreeNode* cur = q.front(); q.pop();
                
                level_last = cur->val;
                
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            
            ans.push_back(level_last);
        }
        
        return ans;
    }
};
