//Runtime: 300 ms, faster than 33.33% of C++ online submissions for Count Good Nodes in Binary Tree.
//Memory Usage: 86.6 MB, less than 100.00% of C++ online submissions for Count Good Nodes in Binary Tree.
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
    int ans;
    
    void dfs(TreeNode* node, int upper){
        if(node == nullptr) return;
        if(node->val >= upper){
            ans++;
        }
        dfs(node->left, max(node->val, upper));
        dfs(node->right, max(node->val, upper));
    };
    
    int goodNodes(TreeNode* root) {
        ans = 0;
        dfs(root, root->val);
        return ans;
    }
};
