/**
Given a Binary Search Tree (BST) with the root node root, return the minimum difference between the values of any two different nodes in the tree.

Example :

Input: root = [4,2,6,1,3,null,null]
Output: 1
Explanation:
Note that root is a TreeNode object, not an array.

The given tree [4,2,6,1,3,null,null] is represented by the following diagram:

          4
        /   \
      2      6
     / \    
    1   3  

while the minimum difference in this tree is 1, it occurs between node 1 and node 2, also between node 3 and node 2.
Note:

The size of the BST will be between 2 and 100.
The BST is always valid, each node's value is an integer, and each node's value is different.
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Minimum Distance Between BST Nodes.
//Memory Usage: 10.8 MB, less than 100.00% of C++ online submissions for Minimum Distance Between BST Nodes.

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
    //initialize for leftmost leaf, 
    //we want the first node->val - last to be very large
    int last = INT_MIN/2;
    int ans = INT_MAX; //need to find min
    
    void inOrder(TreeNode* node){
        if(node->left) inOrder(node->left);
        ans = min(ans, node->val - last);
        last = node->val;
        if(node->right) inOrder(node->right);
    }
    
    int minDiffInBST(TreeNode* root) {
        inOrder(root);
        
        return ans;
    }
};
