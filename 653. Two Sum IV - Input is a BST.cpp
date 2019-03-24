/**
Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.

Example 1:

Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9

Output: True
 

Example 2:

Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28

Output: False
**/

//Runtime: 48 ms, faster than 96.64% of C++ online submissions for Two Sum IV - Input is a BST.
//Memory Usage: 27.3 MB, less than 64.61% of C++ online submissions for Two Sum IV - Input is a BST.

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
    bool findTarget(TreeNode* root, int k) {
        queue<TreeNode*> q;
        vector<int> v; //values seen
        TreeNode* cur;
        
        q.push(root);
        
        while(!q.empty()){
            cur = q.front();
            q.pop();
            
            for(int e : v){
                if(e+cur->val==k){
                    return true;
                }
            }
            v.push_back(cur->val);
            
            if(cur->left) q.push(cur->left);
            if(cur->right) q.push(cur->right);
        }
        
        return false;
    }
};

