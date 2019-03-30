/**
Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7],
  [9,20],
  [3]
]
**/

//Runtime: 8 ms, faster than 100.00% of C++ online submissions for Binary Tree Level Order Traversal II.
//Memory Usage: 13.8 MB, less than 82.65% of C++ online submissions for Binary Tree Level Order Traversal II.

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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if(root == NULL) return vector<vector<int>>();
        queue<TreeNode*> q;
        TreeNode* cur;
        vector<int> level;
        vector<vector<int>> ans;
        int levelCount = 0;
        
        q.push(root);
        levelCount++;
        
        while(!q.empty()){
            cur = q.front();
            q.pop();
            levelCount--;
            
            level.push_back(cur->val);
            
            if(cur->left) q.push(cur->left);
            if(cur->right) q.push(cur->right);
            
            //cur is the last of this level
            if(levelCount == 0){
                ans.push_back(level);
                level = vector<int>();
                //now we have push this node and its sibling's children to queue
                levelCount = q.size();
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
