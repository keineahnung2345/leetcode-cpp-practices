/**
Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

Example:
Given a binary tree 
          1
         / \
        2   3
       / \     
      4   5    
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

Note: The length of path between two nodes is represented by the number of edges between them.
**/

/**
Approach #1: Depth-First Search [Accepted]
Intuition

Any path can be written as two arrows (in different directions) from some node, where an arrow is a path that starts at some node and only travels down to child nodes.

If we knew the maximum length arrows L, R for each child, then the best path touches L + R + 1 nodes.

Algorithm

Let's calculate the depth of a node in the usual way: max(depth of node.left, depth of node.right) + 1. While we do, a path "through" this node uses 1 + (depth of node.left) + (depth of node.right) nodes. Let's search each node and remember the highest number of nodes used in some path. The desired length is 1 minus this number.
**/

/**
Complexity Analysis

Time Complexity: O(N)O(N). We visit every node once.

Space Complexity: O(N)O(N), the size of our implicit call stack during our depth-first search.
**/

//Runtime: 16 ms, faster than 99.19% of C++ online submissions for Diameter of Binary Tree.
//Memory Usage: 19.8 MB, less than 100.00% of C++ online submissions for Diameter of Binary Tree.
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
    int ans;
    int depth(TreeNode* node){
        if(node == NULL) return 0;
        int L = depth(node->left);
        int R = depth(node->right);
        ans = max(ans, L+R);
        return max(L, R) + 1;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        ans = 0;
        depth(root);
        return ans;
    }
};

//stack overflow
/**
class Solution {
public:
    int treeDepth(TreeNode* node){
        if(node == NULL) return 0;
        return 1 + max(treeDepth(node->left), treeDepth(node->right));
    }
    int diameterOfBinaryTree(TreeNode* root) {
        if(root == NULL) return 0;
        return max(
            treeDepth(root->left) + treeDepth(root->right),
            max(diameterOfBinaryTree(root->left),
                diameterOfBinaryTree(root->right)));
    }
};
**/
