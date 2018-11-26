/**
Given the root node of a binary search tree, return the sum of values of all nodes with value between L and R (inclusive).

The binary search tree is guaranteed to have unique values.

 

Example 1:

Input: root = [10,5,15,3,7,null,18], L = 7, R = 15
Output: 32
Example 2:

Input: root = [10,5,15,3,7,13,18,1,null,6], L = 6, R = 10
Output: 23
 

Note:

The number of nodes in the tree is at most 10000.
The final answer is guaranteed to be less than 2^31.
**/

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
Approach 1: Depth First Search
Intuition and Algorithm

We traverse the tree using a depth first search. If node.val falls outside the range [L, R], (for example node.val < L), then we know that only the right branch could have nodes with value inside [L, R].

We showcase two implementations - one using a recursive algorithm, and one using an iterative one.

Complexity Analysis

Time Complexity: O(N), where N is the number of nodes in the tree.

Space Complexity: O(H), where H is the height of the tree. 
**/
class Solution {
public:
//    //recursive method, slower
//     int sum = 0;
//     int rangeSumBST(TreeNode* root, int L, int R) {
//         if(root->left!=NULL){
//             rangeSumBST(root->left, L, R);
//         }
//         if(root->val>=L && root->val<=R){
//             sum+=root->val;
//         }
//         if(root->right!=NULL){
//             rangeSumBST(root->right, L, R);
//         }
//         return sum;
//     }
 
    //iterative method, faster
    int rangeSumBST(TreeNode* root, int L, int R) {
        int sum = 0;
        std::stack<TreeNode*> stack = std::stack<TreeNode*>();
        stack.push(root);
        
        while(!stack.empty()){
            TreeNode* node = stack.top();
            stack.pop(); //it returns NULL!
            
            if(node->val >= L && node->val <= R){
                sum+=node->val;
            }
            //trimming
            // if(node->left!=NULL && node->val >= L){
            if(node->left && node->val >= L){
                stack.push(node->left);
            }
            
            // if(node->right!=NULL && node->val <= R){
            if(node->right && node->val <= R){
                stack.push(node->right);
            }
        }
        return sum;
    }
};
