/**
Given a binary search tree and the lowest and highest boundaries as L and R, trim the tree so that all its elements lies in [L, R] (R >= L). You might need to change the root of the tree, so the result should return the new root of the trimmed binary search tree.

Example 1:
Input: 
    1
   / \
  0   2

  L = 1
  R = 2

Output: 
    1
      \
       2
Example 2:
Input: 
    3
   / \
  0   4
   \
    2
   /
  1

  L = 1
  R = 3

Output: 
      3
     / 
   2   
  /
 1
 **/

/**
Complexity Analysis

Time Complexity: 
O(N), where N is the total number of nodes in the given tree.
We visit each node at most once.

Space Complexity: O(N). 
Even though we don't explicitly use any additional memory, 
the call stack of our recursion could be as large as the number of nodes in the worst case.
**/

//Runtime: 20 ms, faster than 99.78% of C++ online submissions for Trim a Binary Search Tree.
//Memory Usage: 13 MB, less than 100.00% of C++ online submissions for Trim a Binary Search Tree.
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
    //https://www.geeksforgeeks.org/remove-bst-keys-outside-the-given-range/
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        if(root==NULL){
            return NULL;
        }
        
        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);
        
        if(root->val < L){
            TreeNode* newroot = root->right;
            //now that the left subtree falls in [L,R] and root->val < L
            //, it can be inferred that root doesn't have left subtree
            //, so here we only do with right subtree
            // delete root;
            root = NULL;
            return newroot;
        }
        
        if(root->val > R){
            TreeNode* newroot = root->left;
            // delete root;
            root = NULL;
            return newroot;
        }
        
        return root;
    }
};
