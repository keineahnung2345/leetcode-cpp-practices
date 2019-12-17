//Runtime: 24 ms, faster than 72.36% of C++ online submissions for Delete Nodes And Return Forest.
//Memory Usage: 23.1 MB, less than 100.00% of C++ online submissions for Delete Nodes And Return Forest.

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
    vector<TreeNode*> remainings;
    
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        stack<TreeNode*> stk;
        TreeNode* tmp;
        stk.push(root);
        // cout << root->val << " ";
        
        //update "remainings" only at root or when the node's parent is deleted and itself is passed to delNodes
        if(find(to_delete.begin(), to_delete.end(), root->val) == to_delete.end()){
            remainings.push_back(root);
        }
        
        while(!stk.empty()){
            TreeNode* cur = stk.top();
            // cout << cur->val << " ";
            stk.pop();
            
            if(find(to_delete.begin(), to_delete.end(), cur->val) != to_delete.end()){
                if(cur->left) delNodes(cur->left, to_delete);
                if(cur->right) delNodes(cur->right, to_delete);
                cur = NULL;
                break;
            }
            
            if(cur->left && find(to_delete.begin(), to_delete.end(), cur->left->val) != to_delete.end()){
                tmp = cur->left;
                cur->left = NULL;
                if(tmp->left) delNodes(tmp->left, to_delete);
                if(tmp->right) delNodes(tmp->right, to_delete);
            }
            
            if(cur->right && find(to_delete.begin(), to_delete.end(), cur->right->val) != to_delete.end()){
                tmp = cur->right;
                cur->right = NULL;
                if(tmp->left) delNodes(tmp->left, to_delete);
                if(tmp->right) delNodes(tmp->right, to_delete);
            }
            
            if(cur->left) stk.push(cur->left);
            if(cur->right) stk.push(cur->right);
        }
        // cout << endl;
        return remainings;
    }
};
