//Runtime: 44 ms, faster than 63.40% of C++ online submissions for Count Complete Tree Nodes.
//Memory Usage: 31 MB, less than 44.11% of C++ online submissions for Count Complete Tree Nodes.
//time: O(N)
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

//https://leetcode.com/problems/count-complete-tree-nodes/discuss/61958/Concise-Java-solutions-O(log(n)2)
//Runtime: 56 ms, faster than 5.68% of C++ online submissions for Count Complete Tree Nodes.
//Memory Usage: 30.9 MB, less than 67.20% of C++ online submissions for Count Complete Tree Nodes.
//time: O(log(N)^2)
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
    int height(TreeNode* node){
        //define a single tree node having height 0
        //so an empty tree has height -1
        return (node == nullptr) ? -1 : 1 + height(node->left);
    };
    
    int countNodes(TreeNode* root) {
        int h = height(root);
        /*
        if the height of root is negative,
        that means it's an empty tree,
        so there are 0 nodes
        
        o.w. check if right subtree's height is h-1,
        if so, it means the last node appears in right subtree,
        so left subtree is a complete binary tree with height = h-1.
        left subtree has 2^h-1 nodes, plus 1 node for the root itself,
        plus the right subtree's node count
        
        if right subtree's height is not h-1(then it's h-2),
        then the last node appears in left subtree,
        so right subtree is a complete binary tree with height = h-2.
        right subtree has 2^(h-1)-1 nodes, plus 1 node for the root itself,
        plus the left subtree's node count
        */
        return (h < 0) ? 0 : 
            (height(root->right) == h-1) ? (1 << h) + countNodes(root->right) : (1 << h-1) + countNodes(root->left);
    }
};
