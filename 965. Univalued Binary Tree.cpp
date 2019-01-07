/**
A binary tree is univalued if every node in the tree has the same value.

Return true if and only if the given tree is univalued.

 

Example 1:


Input: [1,1,1,1,1,null,1]
Output: true
Example 2:


Input: [2,2,2,5,2]
Output: false
 

Note:

The number of nodes in the given tree will be in the range [1, 100].
Each node's value will be an integer in the range [0, 99].
**/

//Runtime: 4 ms, faster than 93.20% of C++ online submissions for Univalued Binary Tree.
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
    bool isUnivalTree(TreeNode* root) {
        int unival = root->val;
        TreeNode* cur = root;
        queue<TreeNode*> queue;
        queue.push(cur);
        
        while(!queue.empty()){
            if(cur->val!=unival){
                return false;
            }
            if(cur->left!=NULL)
                queue.push(cur->left);
            if(cur->right!=NULL)
                queue.push(cur->right);
            cur = queue.front();
            queue.pop();
        }
        
        return true;
    }
};

/**
Solution
Approach 1: Depth-First Search
Intuition and Algorithm

Let's output all the values of the array. After, we can check that they are all equal.

To output all the values of the array, we perform a depth-first search.
//Java
class Solution {
    List<Integer> vals;
    public boolean isUnivalTree(TreeNode root) {
        vals = new ArrayList();
        dfs(root);
        for (int v: vals)
            if (v != vals.get(0))
                return false;
        return true;
    }

    public void dfs(TreeNode node) {
        if (node != null) {
            vals.add(node.val);
            dfs(node.left);
            dfs(node.right);
        }
    }
}

Complexity Analysis

Time Complexity: O(N), where N is the number of nodes in the given tree.

Space Complexity: O(N). 

Approach 2: Recursion
Intuition and Algorithm

A tree is univalued if both its children are univalued, plus the root node has the same value as the child nodes.

We can write our function recursively. 
left_correct will represent that the left child is correct: 
ie., that it is univalued, and the root value is equal to the left child's value. 
right_correct will represent the same thing for the right child. 
We need both of these properties to be true.

Complexity Analysis

Time Complexity: O(N), where N is the number of nodes in the given tree.

Space Complexity: O(H), where H is the height of the given tree. 

//Runtime: 4 ms, faster than 93.20% of C++ online submissions for Univalued Binary Tree.

class Solution {
public:
    bool isUnivalTree(TreeNode* root) {
        bool left_correct = (root->left==NULL || 
            (root->val == root->left->val && isUnivalTree(root->left)));
        bool right_correct = (root->right==NULL ||
            (root->val == root->right->val && isUnivalTree(root->right)));
        return left_correct && right_correct;
    }
};
**/
