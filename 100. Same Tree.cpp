/**
Given two binary trees, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical and the nodes have the same value.

Example 1:

Input:     1         1
          / \       / \
         2   3     2   3

        [1,2,3],   [1,2,3]

Output: true
Example 2:

Input:     1         1
          /           \
         2             2

        [1,2],     [1,null,2]

Output: false
Example 3:

Input:     1         1
          / \       / \
         2   1     1   2

        [1,2,1],   [1,1,2]

Output: false
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Same Tree.
//Memory Usage: 9.7 MB, less than 99.45% of C++ online submissions for Same Tree.

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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p == NULL && q == NULL){
            return true;
        }else if(p != NULL && q == NULL){
            return false;
        }else if(p == NULL && q != NULL){
            return false;
        }
        
        return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

/**
Approach 1: Recursion
Intuition

The simplest strategy here is to use recursion. Check if p and q nodes are not None, and their values are equal. If all checks are OK, do the same for the child nodes recursively.
**/

/**
Complexity Analysis

Time complexity : \mathcal{O}(N)O(N), where N is a number of nodes in the tree, since one visits each node exactly once.

Space complexity : \mathcal{O}(\log(N))O(log(N)) in the best case of completely balanced tree and \mathcal{O}(N)O(N) in the worst case of completely unbalanced tree, to keep a recursion stack. 
**/

/**
Approach 2: Iteration
Intuition

Start from the root and then at each iteration pop the current node out of the deque. Then do the same checks as in the approach 1 :

p and p are not None,

p.val is equal to q.val,

and if checks are OK, push the child nodes.
**/

/**
Complexity Analysis

Time complexity : \mathcal{O}(N)O(N) since each node is visited exactly once.

Space complexity : \mathcal{O}(\log(N))O(log(N)) in the best case of completely balanced tree and \mathcal{O}(N)O(N) in the worst case of completely unbalanced tree, to keep a deque.
**/

/**
class Solution {
public:
    bool check(TreeNode* p, TreeNode* q){
        //this function check current node
        if(p == NULL && q == NULL) return true;
        if(p == NULL || q == NULL) return false;
        if(p->val != q->val) return false;
        return true;
    }
    bool isSameTree(TreeNode* p, TreeNode* q) {
        //if check returns true, there are two cases needed to be handled differently
        //if check returns false, just return false
        if(p == NULL && q == NULL) return true;
        if(!check(p, q)) return false;
        
        queue<TreeNode*> q1, q2;
        
        q1.push(p);
        q2.push(q);
        
        while(!q1.empty()){
            p = q1.front(); q1.pop();
            q = q2.front(); q2.pop();
            
            if(p == NULL && q == NULL) continue;
            if(!check(p, q)) return false;
            //now both p and q are not NULL
            
            if(!check(p->left, q->left)) return false;
            if(p->left != NULL){
                q1.push(p->left);
                q2.push(q->left);
            }
            
            if(!check(p->right, q->right)) return false;
            if(p->right != NULL){
                q1.push(p->right);
                q2.push(q->right);
            }
        }
        
        return true;
    }
};
**/
