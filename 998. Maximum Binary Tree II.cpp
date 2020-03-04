//https://leetcode.com/problems/maximum-binary-tree-ii/discuss/242936/JavaC%2B%2BPython-Recursion-and-Iteration
//Solution 1: Recursion
//time: O(n), space: O(n)
//Runtime: 4 ms, faster than 89.46% of C++ online submissions for Maximum Binary Tree II.
//Memory Usage: 13.1 MB, less than 20.00% of C++ online submissions for Maximum Binary Tree II.

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
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        if(root && root->val > val){
            //operate on its right subtree and then return
            root->right = insertIntoMaxTree(root->right, val);
            return root;
        }
        //null node or root->val <= val 
        TreeNode* node = new TreeNode(val);
        node->left = root;
        return node;
    }
};

//Solution 2: Iteration
//Runtime: 4 ms, faster than 89.46% of C++ online submissions for Maximum Binary Tree II.
//Memory Usage: 13.5 MB, less than 20.00% of C++ online submissions for Maximum Binary Tree II.
//time: O(n), space: O(1)
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
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        TreeNode *node = new TreeNode(val), *cur = root;
        if(root->val < val){
            node->left = root;
            return node;
        }
        while(cur->right && cur->right->val > val){
            cur = cur->right;
        }
        node->left = cur->right;
        cur->right = node;
        return root;
    }
};
