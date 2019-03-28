/**
Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

Example:

Input:

   1
    \
     3
    /
   2

Output:
1

Explanation:
The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).
 

Note: There are at least two nodes in this BST.
**/

//Runtime: 36 ms, faster than 22.95% of C++ online submissions for Minimum Absolute Difference in BST.
//Memory Usage: 21.8 MB, less than 96.61% of C++ online submissions for Minimum Absolute Difference in BST.
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
    int last = INT_MIN/2;
    int ans = INT_MAX;
    
    void inOrder(TreeNode* node){
        if(node->left) inOrder(node->left);
        ans = min(ans, node->val - last);
        last = node->val;
        if(node->right) inOrder(node->right);
    }
    int getMinimumDifference(TreeNode* root) {
        inOrder(root);
        return ans;
    }
};
