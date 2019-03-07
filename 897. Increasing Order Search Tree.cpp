/**
Given a tree, rearrange the tree in in-order so that the leftmost node in the tree is now the root of the tree, and every node has no left child and only 1 right child.

Example 1:
Input: [5,3,6,2,4,null,8,1,null,null,null,7,9]

       5
      / \
    3    6
   / \    \
  2   4    8
 /        / \ 
1        7   9

Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

 1
  \
   2
    \
     3
      \
       4
        \
         5
          \
           6
            \
             7
              \
               8
                \
                 9  
Note:

The number of nodes in the given tree will be between 1 and 100.
Each node will have a unique integer value from 0 to 1000.
**/

//Runtime: 72 ms, faster than 56.90% of C++ online submissions for Increasing Order Search Tree.
//Memory Usage: 37.7 MB, less than 5.68% of C++ online submissions for Increasing Order Search Tree.
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
    TreeNode* increasingBST(TreeNode* root) {
        //in-order traversal
        stack<TreeNode*> stk;
        TreeNode* cur = root;
        TreeNode* newcur = NULL;
        TreeNode* newroot = NULL;
        bool isFirst = true;
        
        while(cur!=NULL || stk.size() > 0){
            while(cur!=NULL){
                stk.push(cur);
                cur = cur->left;
            }
            cur = stk.top();
            stk.pop();
            
            TreeNode node = TreeNode(cur->val);
            if(isFirst){
                newroot = new TreeNode(cur->val);
                newcur = newroot;
                isFirst = !isFirst;
            }else{
                newcur->right = new TreeNode(cur->val);
                newcur = newcur->right;
            }
            
            cur = cur->right;
        }
        
        return newroot;
    }
};

//Approach 1: In-Order Traversal
//Runtime: 72 ms, faster than 56.90% of C++ online submissions for Increasing Order Search Tree.
//Memory Usage: 37 MB, less than 18.44% of C++ online submissions for Increasing Order Search Tree.
/**
Complexity Analysis

Time Complexity: O(N)O(N), where NN is the number of nodes in the given tree.

Space Complexity: O(N)O(N), the size of the answer. 
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
 
 /**
class Solution {
public:
    void inOrder(TreeNode* root, vector<int>& values){
        if(root==NULL) return;
        inOrder(root->left, values);
        values.push_back(root->val);
        inOrder(root->right, values);
    }
    
    TreeNode* increasingBST(TreeNode* root) {
        vector<int> values;
        inOrder(root, values);
        
        TreeNode* newcur = new TreeNode(0);
        TreeNode* newroot = newcur;
        
        for(auto val : values){
            newcur->right = new TreeNode(val);
            newcur = newcur->right;
        }
        
        return newroot->right;
    }
};
**/

/**
Approach 2: Traversal with Relinking
Intuition and Algorithm

We can perform the same in-order traversal as in Approach 1. 
During the traversal, we'll construct the answer on the fly, 
reusing the nodes of the given tree by cutting their left child and adjoining them to the answer.
**/

/**
Time Limit Exceeded
Last executed input
[379
826]
**/

/**
class Solution {
public:
    TreeNode* newcur;
    
    void inOrder(TreeNode* node){
        if(node==NULL) return;
        inOrder(node->left);
        newcur->left = NULL;
        newcur->right = node;
        newcur = node;
        inOrder(node->right);
    }
    
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode* newroot = new TreeNode(0);
        newcur = newroot;
        inOrder(root);
        return newroot->right;
    }
};
**/


