/**
Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

Given binary search tree:  root = [6,2,8,0,4,7,9,null,null,3,5]

Example 1:

Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Explanation: The LCA of nodes 2 and 8 is 6.
Example 2:

Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.

Note:

All of the nodes' values will be unique.
p and q are different and both values will exist in the BST.
**/

//Runtime: 48 ms, faster than 50.56% of C++ online submissions for Lowest Common Ancestor of a Binary Search Tree.
//Memory Usage: 27.5 MB, less than 5.39% of C++ online submissions for Lowest Common Ancestor of a Binary Search Tree.
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
    void dfs(TreeNode* root, int depth, vector<TreeNode*>& visited, vector<int>& depths){
        if(root==NULL) return;
        dfs(root->left, depth+1, visited, depths);
        dfs(root->right, depth+1, visited, depths);
        visited.push_back(root);
        depths.push_back(depth+1);
    }
    
    void fillPath(vector<TreeNode*>& visited, vector<int>& depths, vector<TreeNode*>& path, TreeNode* node){
        int depth;
        for(int i = 0; i < visited.size(); i++){
            if(visited[i]==node){
                path.push_back(visited[i]);
                depth = depths[i];
                depth--;
            }else if(depths[i]==depth){
                path.push_back(visited[i]);
                depth--;
            }
        }
    }
    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> visited;
        vector<int> depths;
        
        dfs(root, 0, visited, depths);
        
        //record the path to p & q
        vector<TreeNode*> pPath, qPath;
        fillPath(visited, depths, pPath, p);
        fillPath(visited, depths, qPath, q);
        
        TreeNode* prev = 0;
        for(int i = 0; i < pPath.size() && i < qPath.size(); i++){
            if(pPath[pPath.size()-1-i]!=qPath[qPath.size()-1-i]){
                return prev;
            }
            prev = pPath[pPath.size()-1-i];
        }
        
        return prev;
    }
};

/**
Approach 1: Recursive Approach
Intuition

Lowest common ancestor for two nodes p and q would be the last ancestor node common to both of them. 
Here last is defined in terms of the depth of the node. 
The below diagram would help in understanding what lowest means.
Note: One of p or q would be in the left subtree and the other in the right subtree of the LCA node.

Algorithm

Start traversing the tree from the root node.
If both the nodes p and q are in the right subtree, then continue the search with right subtree starting step 1.
If both the nodes p and q are in the left subtree, then continue the search with left subtree starting step 1.
If both step 2 and step 3 are not true, this means we have found the node which is common to node p's and q's subtrees. 
and hence we return this common node as the LCA.
**/

/**
Complexity Analysis
Time Complexity: O(N), where N is the number of nodes in the BST. 
In the worst case we might be visiting all the nodes of the BST.

Space Complexity: O(N). This is because the maximum amount of space 
utilized by the recursion stack would be NN since the height of a skewed BST could be N. 
**/

//Runtime: 56 ms, faster than 11.43% of C++ online submissions for Lowest Common Ancestor of a Binary Search Tree.
//Memory Usage: 25.8 MB, less than 63.85% of C++ online submissions for Lowest Common Ancestor of a Binary Search Tree.
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(p->val > root->val && q->val > root->val){
            //both on right side
            return lowestCommonAncestor(root->right, p, q);
        }else if(p->val < root->val && q->val < root->val){
            //both on left side
            return lowestCommonAncestor(root->left, p, q);
        // }else if((p->val - root->val) * (q->val - root->val) < 0 || root==p || root==q){
        }else {
            //p and q are on the two sides of root
            //or one of p or q is root
            return root;
        }
        return NULL;
    }
};


//iterative
/**
Approach 2: Iterative Approach
Algorithm

The steps taken are also similar to approach 1. 
The only difference is instead of recursively calling the function, 
we traverse down the tree iteratively. 
This is possible without using a stack or recursion since we don't need to backtrace to find the LCA node. 
In essence of it the problem is iterative, it just wants us to find the split point. 
The point from where p and q won't be part of the same subtree or when one is the parent of the other.
**/

//Runtime: 56 ms, faster than 11.43% of C++ online submissions for Lowest Common Ancestor of a Binary Search Tree.
//Memory Usage: 25.9 MB, less than 34.62% of C++ online submissions for Lowest Common Ancestor of a Binary Search Tree.
/**
Complexity Analysis
Time Complexity : O(N), where N is the number of nodes in the BST. 
In the worst case we might be visiting all the nodes of the BST.
Space Complexity : O(1). 
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {  
        TreeNode* cur = root;
        while(cur!=NULL){
            if(p->val > cur->val && q->val > cur->val){
                cur = cur->right;
            }else if(p->val < cur->val && q->val < cur->val){
                cur = cur->left;
            }else {
                return cur;
            }
        }
        return NULL;
    }
};

