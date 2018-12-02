/**
We are given the head node root of a binary tree, where additionally every node's value is either a 0 or a 1.

Return the same tree where every subtree (of the given tree) not containing a 1 has been removed.

(Recall that the subtree of a node X is X, plus every node that is a descendant of X.)

Example 1:
Input: [1,null,0,0,1]
Output: [1,null,0,null,1]
 
Explanation: 
Only the red nodes satisfy the property "every subtree not containing a 1".
The diagram on the right represents the answer.


Example 2:
Input: [1,0,1,0,0,0,1]
Output: [1,null,1,null,1]



Example 3:
Input: [1,1,0,1,1,0,1,0]
Output: [1,1,0,1,1,null,1]



Note:

The binary tree will have at most 100 nodes.
The value of each node will only be 0 or 1.
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
/**
Wrong Answer
class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        //use DFS
        if(root==NULL){ //empty node
            return NULL;
        }else if(root->left==NULL && root->right==NULL && root->val==0){ //empty subtree
            return NULL;
        }else{
            root->left = pruneTree(root->left);
            root->right = pruneTree(root->right);
        }
        return root;
    }
};
//the combine step:
if(root->left==NULL && root->right==NULL && root->val==0){ //empty subtree
    return NULL;
should be put after divide step:
root->left = pruneTree(root->left);
root->right = pruneTree(root->right);
!
**/
class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        if(root==NULL){ //empty node
            return NULL;
        }
        //use DFS
        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);
        //divide and conquer
        if(root->left==NULL && root->right==NULL && root->val==0){ //empty subtree
            return NULL;
        }
        return root;
    }
};

/**
Approach #1: Recursion [Accepted]
Intuition

Prune children of the tree recursively. The only decisions at each node are whether to prune the left child or the right child.

Algorithm

We'll use a function containsOne(node) that does two things: it tells us whether the subtree at this node contains a 1, and it also prunes all subtrees not containing 1.

If for example, node.left does not contain a one, then we should prune it via node.left = null.

Also, the parent needs to be checked. If for example the tree is a single node 0, the answer is an empty tree.

//Java
class Solution {
    public TreeNode pruneTree(TreeNode root) {
        return containsOne(root) ? root : null;
    }

    public boolean containsOne(TreeNode node) {
        if (node == null) return false;
        boolean a1 = containsOne(node.left);
        boolean a2 = containsOne(node.right);
        if (!a1) node.left = null;
        if (!a2) node.right = null;
        return node.val == 1 || a1 || a2;
    }
}

Complexity Analysis

Time Complexity: O(N), where N is the number of nodes in the tree. We process each node once.

Space Complexity: O(H), where H is the height of the tree. This represents the size of the implicit call stack in our recursion.
**/
