/**
Given a binary tree, return all root-to-leaf paths.

Note: A leaf is a node with no children.

Example:

Input:

   1
 /   \
2     3
 \
  5

Output: ["1->2->5", "1->3"]

Explanation: All root-to-leaf paths are: 1->2->5, 1->3
**/

//Runtime: 8 ms, faster than 98.26% of C++ online submissions for Binary Tree Paths.
//Memory Usage: 11.7 MB, less than 91.86% of C++ online submissions for Binary Tree Paths.

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
    vector<string> binaryTreePaths(TreeNode* root) {
        if(root == NULL) return vector<string>();
        //leaf node
        if(!root->left && !root->right)
            return vector<string> {to_string(root->val)};
        vector<string> ans;
        if(root->left){
            for(string s : binaryTreePaths(root->left)){
                ans.push_back(to_string(root->val)+"->"+s);
                // cout << to_string(root->val)+"->"+s << endl;
            }
        }
        if(root->right){
            for(string s : binaryTreePaths(root->right)){
                ans.push_back(to_string(root->val)+"->"+s);
                // cout << to_string(root->val)+"->"+s << endl;
            }
        }
        return ans;
    }
};
