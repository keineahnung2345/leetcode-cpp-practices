/**
In a binary tree, the root node is at depth 0, and children of each depth k node are at depth k+1.

Two nodes of a binary tree are cousins if they have the same depth, but have different parents.

We are given the root of a binary tree with unique values, and the values x and y of two different nodes in the tree.

Return true if and only if the nodes corresponding to the values x and y are cousins.

Example 1:


Input: root = [1,2,3,4], x = 4, y = 3
Output: false
Example 2:


Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
Output: true
Example 3:



Input: root = [1,2,3,null,4], x = 2, y = 3
Output: false
 

Note:

The number of nodes in the tree will be between 2 and 100.
Each node has a unique integer value from 1 to 100.
**/

/**
Approach 1: Annotate Parent and Depth
Intuition

Nodes are cousins if they have the same depth but different parents. 
A straightforward approach is to be able to know the parent and depth of each node.

Algorithm

We can use a depth-first search to annotate each node. 
For each node with parent par and depth d, we will record results in hashmaps: 
parent[node.val] = par and depth[node.val] = d.
**/

/**
Complexity Analysis

Time Complexity: O(N), where N is the number of nodes in the tree.

Space Complexity: O(N). 
**/

//Runtime: 12 ms, faster than 23.79% of C++ online submissions for Cousins in Binary Tree.
//Memory Usage: 15.5 MB, less than 5.08% of C++ online submissions for Cousins in Binary Tree.

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
    map<int, int> depth;
    map<int, TreeNode*> parent;
    
    void dfs(TreeNode* node, TreeNode* par){
        if(node!=NULL){
            cout << node-> val;
            depth[node->val] = par!=NULL?1+depth[par->val]:0;
            //can't use parent.insert(node->val, par)!
            parent[node->val] = par;
            dfs(node->left, node);
            dfs(node->right, node);
        }
    }
    
    bool isCousins(TreeNode* root, int x, int y) {
        dfs(root, NULL);
        return (depth[x] == depth[y] && parent[x] != parent[y]);
    }
};
