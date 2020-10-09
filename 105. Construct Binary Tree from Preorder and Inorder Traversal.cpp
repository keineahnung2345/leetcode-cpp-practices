//Runtime: 76 ms, faster than 12.67% of C++ online submissions for Construct Binary Tree from Preorder and Inorder Traversal.
//Memory Usage: 75.4 MB, less than 5.21% of C++ online submissions for Construct Binary Tree from Preorder and Inorder Traversal.
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty()) return nullptr;
        
        TreeNode* root = new TreeNode(preorder[0]);
        
        int split = find(inorder.begin(), inorder.end(), preorder[0]) - inorder.begin();
        
        vector<int> linorder(inorder.begin(), inorder.begin()+split);
        vector<int> lpreorder(preorder.begin()+1, preorder.begin()+1+linorder.size());
        root->left = buildTree(lpreorder, linorder);
        
        vector<int> rpreorder(preorder.begin()+1+linorder.size(), preorder.end());
        vector<int> rinorder(inorder.begin()+split+1, inorder.end());
        root->right = buildTree(rpreorder, rinorder);
        
        return root;
    }
};
