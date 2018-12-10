/**
For a binary tree T, we can define a flip operation as follows: choose any node, and swap the left and right child subtrees.

A binary tree X is flip equivalent to a binary tree Y if and only if we can make X equal to Y after some number of flip operations.

Write a function that determines whether two binary trees are flip equivalent.  The trees are given by root nodes root1 and root2.

 

Example 1:

Input: root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 = [1,3,2,null,6,4,5,null,null,null,null,8,7]
Output: true
Explanation: We flipped at nodes with values 1, 3, and 5.
Flipped Trees Diagram
 

Note:

Each tree will have at most 100 nodes.
Each value in each tree will be a unique integer in the range [0, 99].
**/

//Your runtime beats 100.00 % of cpp submissions.
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
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        if(root1==NULL && root2==NULL){
            return true;
        }else if(root1==NULL ^ root2==NULL){
            return false;
        }else if(root1->val != root2->val){
            return false;
        }else{
            return (flipEquiv(root1->left, root2->left) && flipEquiv(root1->right, root2->right)) ||
                (flipEquiv(root1->left, root2->right) && flipEquiv(root1->right, root2->left));
        }
    }
};

/**
Solution
Approach 1: Recursion
Intuition

If root1 and root2 have the same root value, then we only need to check if their children are equal (up to ordering.)

Algorithm

There are 3 cases:

If root1 or root2 is null, then they are equivalent if and only if they are both null.

Else, if root1 and root2 have different values, they aren't equivalent.

Else, let's check whether the children of root1 are equivalent to the children of root2. 
There are two different ways to pair these children.
**/

//Java
/**
class Solution {
    public boolean flipEquiv(TreeNode root1, TreeNode root2) {
        if (root1 == root2)
            return true;
        if (root1 == null || root2 == null || root1.val != root2.val)
            return false;

        return (flipEquiv(root1.left, root2.left) && flipEquiv(root1.right, root2.right) ||
                flipEquiv(root1.left, root2.right) && flipEquiv(root1.right, root2.left));
    }
}
**/

/**
Complexity Analysis

Time Complexity: O(min(N_1, N_2)), where N_1, N_2 are the lengths of root1 and root2.

Space Complexity: O(min(H_1, H_2)), where H_1, H_2 are the heights of the trees of root1 and root2. 
**/

/**
Approach 2: Canonical Traversal
Intuition

Flip each node so that the left child is smaller than the right, and call this the canonical representation. All equivalent trees have exactly one canonical representation.

Algorithm

We can use a depth-first search to compare the canonical representation of each tree. If the traversals are the same, the representations are equal.

When traversing, we should be careful to encode both when we enter or leave a node.
**/

//Your runtime beats 100.00 % of cpp submissions.
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
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        vector<int> l1, l2;
        
        dfs(root1, l1);
        dfs(root2, l2);
        
        // std::copy(l1.begin(), l1.end(), std::ostream_iterator<int>(std::cout, " "));
        // cout << endl;
        // std::copy(l2.begin(), l2.end(), std::ostream_iterator<int>(std::cout, " "));
        
        return l1==l2;
    }
    
    void dfs(TreeNode* node, vector<int>& v){
        if(node==NULL) return;
        v.push_back(node->val);
        
        int L = node->left==NULL?-1:node->left->val;
        int R = node->right==NULL?-1:node->right->val;
        
        if(L<R){
            dfs(node->left, v);
            dfs(node->right, v);
        }else{
            dfs(node->right, v);
            dfs(node->left, v);
        }
    }
};

/**
Complexity Analysis

Time Complexity: O(N_1 + N_2), where N_1, N_2 are the lengths of root1 and root2. (In Python, this is min(N_1, N_2).)

Space Complexity: O(N_1 + N_2). (In Python, this is min(H_1, H_2), where H_1, H_2 are the heights of the trees of root1 and root2.) 
**/
