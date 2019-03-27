/**
Given a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus sum of all keys greater than the original key in BST.

Example:

Input: The root of a Binary Search Tree like this:
              5
            /   \
           2     13

Output: The root of a Greater Tree like this:
             18
            /   \
          20     13
**/

//Runtime: 52 ms, faster than 43.25% of C++ online submissions for Convert BST to Greater Tree.
//Memory Usage: 23.6 MB, less than 100.00% of C++ online submissions for Convert BST to Greater Tree.
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
    int sum = 0;
    
    void inOrder(TreeNode* root){
        //reversed inorder traversal
        if(!root) return;
        if(root->right) inOrder(root->right);
        int temp = root->val;
        root->val += sum;
        sum += temp;
        if(root->left) inOrder(root->left);
    }
    
    TreeNode* convertBST(TreeNode* root) {
        inOrder(root);
        
        return root;
    }
};
