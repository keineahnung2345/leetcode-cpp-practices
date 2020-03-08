//Recursive
//Runtime: 4 ms, faster than 56.80% of C++ online submissions for Binary Tree Inorder Traversal.
//Memory Usage: 9.3 MB, less than 77.00% of C++ online submissions for Binary Tree Inorder Traversal.
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
    
    void inorderTraversalR(TreeNode* root){
        if(!root) return;
        if(root->left){
            inorderTraversal(root->left);
        }
        ans.push_back(root->val);
        if(root->right){
            inorderTraversal(root->right);
        }
    }
    
    vector<int> inorderTraversal(TreeNode* root) {
        inorderTraversalR(root);
        return ans;
    }
};

//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Binary Tree Inorder Traversal.
//Memory Usage: 8 MB, less than 100.00% of C++ online submissions for Binary Tree Inorder Traversal.
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
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
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> stk;
        TreeNode* cur = root;
        vector<int> ans;
        
        stk.push(cur);
        
        do{
            cur = stk.top();
            
            //go to its leftmost child
            TreeNode* tmp = cur ? cur->left : NULL;
            while(tmp){
                stk.push(tmp);
                tmp = tmp->left;
            }
            
            //if it has left child, process leftmost child first
            cur = stk.top(); stk.pop();
            if(cur) ans.push_back(cur->val);
            
            //cut current node and its parent, 
            //so current node won't be traversed again
            if(stk.size() > 0) stk.top()->left = NULL;
            
            //deal with right child
            if(cur && cur->right) stk.push(cur->right);
        }while(!stk.empty());
        
        return ans;
    }
};

//iterative, another version
//Runtime: 4 ms, faster than 56.80% of C++ online submissions for Binary Tree Inorder Traversal.
//Memory Usage: 8 MB, less than 100.00% of C++ online submissions for Binary Tree Inorder Traversal.
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode*> stk;
        TreeNode* cur;
        
        stk.push(root);
        
        while(!stk.empty()){
            cur = stk.top();
            while(cur && cur->left){
                stk.push(cur->left);
                cur = cur->left;
            }
            cur = stk.top(); stk.pop();
            if(cur) ans.push_back(cur->val);
            if(stk.size() > 0) stk.top()->left = nullptr;
            if(cur && cur->right) stk.push(cur->right);
        }
        
        return ans;
    }
};
