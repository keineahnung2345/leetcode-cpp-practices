//Runtime: 4 ms, faster than 97.16% of C++ online submissions for Flatten Binary Tree to Linked List.
//Memory Usage: 13.3 MB, less than 59.25% of C++ online submissions for Flatten Binary Tree to Linked List.
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
    void preorder(TreeNode* node, vector<TreeNode*>& nodes){
        if(!node) return;
        
        nodes.push_back(node);
        preorder(node->left, nodes);
        preorder(node->right, nodes);
    }
    
    void flatten(TreeNode* root) {
        vector<TreeNode*> nodes;
        preorder(root, nodes);
        
        // cout << "nodes: " << nodes.size() << endl;
        
        for(int i = 0; i+1 < nodes.size(); ++i){
            nodes[i]->left = nullptr;
            nodes[i]->right = nodes[i+1];
        }
    }
};

//post order traversal
//https://leetcode.com/problems/flatten-binary-tree-to-linked-list/discuss/36977/My-short-post-order-traversal-Java-solution-for-share
//Runtime: 12 ms, faster than 31.00% of C++ online submissions for Flatten Binary Tree to Linked List.
//Memory Usage: 12.9 MB, less than 59.25% of C++ online submissions for Flatten Binary Tree to Linked List.
class Solution {
public:
    TreeNode* prev;
    
    void flatten(TreeNode* root) {
        if(!root) return;
        //post-order traversal
        //visit right child -> left child -> itself
        flatten(root->right);
        flatten(root->left);
        //prev will be its successor in in-order traversal!
        root->right = prev;
        root->left = nullptr;
        prev = root;
    }
};
