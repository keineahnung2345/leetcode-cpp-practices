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

//iterative
//https://leetcode.com/problems/flatten-binary-tree-to-linked-list/discuss/37010/Share-my-simple-NON-recursive-solution-O(1)-space-complexity!
//Runtime: 4 ms, faster than 97.16% of C++ online submissions for Flatten Binary Tree to Linked List.
//Memory Usage: 13 MB, less than 59.25% of C++ online submissions for Flatten Binary Tree to Linked List.
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode* cur = root;
        
        while(cur){
            if(cur->left){
                TreeNode* prev = cur->left;
                
                while(prev->right) prev = prev->right;
                //now prev is cur's predecessor in in-order traversal
                //it's also rightmost node of cur's left subtree
                
                //let cur's right subtree be cur's left subtree's descendants
                //prev->right must be nullptr, so this op is safe
                prev->right = cur->right;
                //move cur's left subtree to the right
                cur->right = cur->left;
                //the reconstructed tree don't have left children
                cur->left = nullptr;
            }
            
            //move forward in the reconstructed tree
            cur = cur->right;
        }
    }
};
