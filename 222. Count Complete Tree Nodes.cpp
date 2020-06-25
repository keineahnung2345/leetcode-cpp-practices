//Runtime: 44 ms, faster than 63.40% of C++ online submissions for Count Complete Tree Nodes.
//Memory Usage: 31 MB, less than 44.11% of C++ online submissions for Count Complete Tree Nodes.
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int countNodes(TreeNode* root) {
        if(root == nullptr){
            return 0;
        }
        
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};
