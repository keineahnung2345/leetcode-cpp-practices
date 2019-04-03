//Runtime: 32 ms, faster than 99.05% of C++ online submissions for Subtree of Another Tree.
//Memory Usage: 20.9 MB, less than 99.03% of C++ online submissions for Subtree of Another Tree.

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
    bool isSameTree(TreeNode* s, TreeNode* t){
        //this version not allow search t in s's subtree,
        //it just compare whether s equals to t
        if(!s && !t) return true;
        if(!s || !t) return false;
        if(s->val != t->val) return false;
        return isSameTree(s->left, t->left) && isSameTree(s->right, t->right);
    }
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if(!s && !t) return true;
        if(!s || !t) return false;
        //both not empty
        //s and t are same tree
        if((s->val == t->val) && isSameTree(s->left, t->left) && isSameTree(s->right, t->right)) return true;
        //if s and t are not the same,
        //keep find t in s's subtree
        return isSubtree(s->left, t) || isSubtree(s->right, t);
    }
};

/**
Approach #1 Using Preorder Traversal [Accepted]
preorder traverse a tree and build a string
then check for substring
**/

/**
Complexity Analysis

Time complexity : O(m^2+n^2+m*n). 
A total of nn nodes of the tree s and m nodes of tree t are traversed. 
Assuming string concatenation takes O(k) time for strings of length k and indexOf takes O(m*n).

Space complexity : O(max(m,n)). The depth of the recursion tree can go upto n for tree t and m for tree s in worst case.
**/

/**
class Solution {
public:
    string preorder(TreeNode* root, bool left){
        if(!root){
            if(left) return "null";
            else return "null";
        }
        return "#" + to_string(root->val) + " " + preorder(root->left, true) + " " + preorder(root->right, false);
    }
    bool isSubtree(TreeNode* s, TreeNode* t) {
        //if root is not NULL, then the 2nd parameter doesn't matter
        string s1 = preorder(s, true);
        string s2 = preorder(t, true);
        return s1.find(s2)!=string::npos;
    }
};
**/

/**
Approach #2 By Comparison of Nodes [Accepted]
**/

/**
Complexity Analysis

Time complexity : O(m*n)O(m∗n). In worst case(skewed tree) traverse function takes O(m*n)O(m∗n) time.

Space complexity : O(n)O(n). The depth of the recursion tree can go upto nn. nn refers to the number of nodes in ss.
**/

/**
class Solution {
public:
    bool equals(TreeNode* s, TreeNode* t){
        if(!s && !t) return true;
        if(!s || !t) return false;
        return s->val == t->val && equals(s->left, t->left) && equals(s->right, t->right);
    }
    bool traverse(TreeNode* s, TreeNode* t){
        if(s == NULL) return false;
        return equals(s, t) || traverse(s->left, t) || traverse(s->right, t);
    }
    bool isSubtree(TreeNode* s, TreeNode* t) {
        return traverse(s, t);
    }
};
**/
