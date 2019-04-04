//Runtime: 40 ms, faster than 5.25% of C++ online submissions for Balanced Binary Tree.
//Memory Usage: 17.3 MB, less than 72.64% of C++ online submissions for Balanced Binary Tree.

https://leetcode.com/problems/balanced-binary-tree/discuss/35691/The-bottom-up-O(N)-solution-would-be-better

/**
top-down approach
time complexity: 
treeDepth needs O(n), and we need to calculate for every node, so total O(n^2)
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
class Solution {
public:
    int treeDepth(TreeNode* root){
        if(root == NULL) return 0;
        return 1 + max(treeDepth(root->left), treeDepth(root->right));
    }
    // bool isSubtreeBalanced(TreeNode* root){
    //     if(root == NULL) return true;
    //     return abs(treeDepth(root->left) - treeDepth(root->right)) <= 1;
    // }
    bool isBalanced(TreeNode* root) {
        if(root == NULL) return true;
        // return isSubtreeBalanced(root) && isSubtreeBalanced(root->left) && isSubtreeBalanced(root->right);
        // cout << root->val << endl;
        // if(abs(treeDepth(root->left) - treeDepth(root->right)) > 1){
        //     cout << "***" << root->val << "***" << endl;
        //     cout << (root->left->val) << " " <<(root->right->val) << endl;
        //     cout << treeDepth(root->left) << " " << treeDepth(root->right) << endl;
        // }
        return (abs(treeDepth(root->left) - treeDepth(root->right)) <= 1) && isBalanced(root->left) && isBalanced(root->right);
    }
};

/**
bottom-up approach
time complexity: O(n)
**/

//Runtime: 16 ms, faster than 99.39% of C++ online submissions for Balanced Binary Tree.
//Memory Usage: 17.1 MB, less than 88.68% of C++ online submissions for Balanced Binary Tree.

/**
class Solution {
public:
    int dfsHeight(TreeNode* root){
        if(!root) return 0;
        int left = dfsHeight(root->left);
        if(left == -1) return -1;
        int right = dfsHeight(root->right);
        if(right == -1) return -1;
        if(abs(left - right) > 1) return -1;
        return max(left, right)+1;
    }
    bool isBalanced(TreeNode* root) {
        return dfsHeight(root) != -1;
    }
};
**/
