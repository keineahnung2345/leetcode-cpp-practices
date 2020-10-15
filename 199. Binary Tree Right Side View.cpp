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

//dfs, preorder
//Runtime: 4 ms, faster than 79.52% of C++ online submissions for Binary Tree Right Side View.
//Memory Usage: 12.2 MB, less than 5.48% of C++ online submissions for Binary Tree Right Side View.
class Solution {
public:
    vector<int> ans;
    
    void preorder(TreeNode* node, int depth){
        if(!node) return;
        
        /*
        only push value to the vector 
        when we meet first element in that depth
        
        note that right child is visited before left child,
        so the first element in that depth will be
        the rightmost node in that depth
        */
        if(depth == ans.size()){
            ans.push_back(node->val);
        }
        
        preorder(node->right, depth+1);
        preorder(node->left, depth+1);
    }
    
    vector<int> rightSideView(TreeNode* root) {
        preorder(root, 0);
        
        return ans;
    }
};
