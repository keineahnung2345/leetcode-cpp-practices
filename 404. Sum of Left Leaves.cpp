/**
Find the sum of all left leaves in a given binary tree.

Example:

    3
   / \
  9  20
    /  \
   15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.
**/

//Runtime: 8 ms, faster than 100.00% of C++ online submissions for Sum of Left Leaves.
//Memory Usage: 13.5 MB, less than 100.00% of C++ online submissions for Sum of Left Leaves.
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
    int ans;
    
    void rSumOfLeftLeaves(TreeNode* node, bool isLeft){
        // cout << node->val << " " << isLeft << endl;
        if(node->left == NULL && node->right == NULL && isLeft){
            ans += node->val;
        }
        if(node->left){
            rSumOfLeftLeaves(node->left, true);
        }
        if(node->right){
            rSumOfLeftLeaves(node->right, false);
        }
    }
    
    int sumOfLeftLeaves(TreeNode* root) {
        if(root == NULL) return 0;
        
        ans = 0;
        rSumOfLeftLeaves(root, false);
        
        return ans;
    }
};
