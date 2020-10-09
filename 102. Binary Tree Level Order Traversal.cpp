//BFS
//Runtime: 4 ms, faster than 88.94% of C++ online submissions for Binary Tree Level Order Traversal.
//Memory Usage: 13 MB, less than 17.26% of C++ online submissions for Binary Tree Level Order Traversal.
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        vector<vector<int>> ans;
        
        if(root) q.push(root);
        
        while(!q.empty()){
            int level_size = q.size();
            
            vector<int> level;
            
            while(level_size-- > 0){
                TreeNode* cur = q.front(); q.pop();
                
                level.push_back(cur->val);
                
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            
            ans.push_back(level);
        }
        
        return ans;
    }
};
