/**
Consider all the leaves of a binary tree.  From left to right order, the values of those leaves form a leaf value sequence.

For example, in the given tree above, the leaf value sequence is (6, 7, 4, 9, 8).

Two binary trees are considered leaf-similar if their leaf value sequence is the same.

Return true if and only if the two given trees with head nodes root1 and root2 are leaf-similar.

Note:

Both of the given trees will have between 1 and 100 nodes.
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
 
//Runtime: 4 ms, faster than 57.23% of C++ online submissions for Leaf-Similar Trees.
class Solution {
public:
    void build_leaf_values(TreeNode* root, vector<int>* leaf_values){
        stack<TreeNode*> stk;
        TreeNode* cur;
        
        stk.push(root);
        while(!stk.empty()){
            cur = stk.top();
            stk.pop();
            
            if(cur->left==NULL && cur->right==NULL){
                leaf_values->push_back(cur->val);
            }else{
                if(cur->right) stk.push(cur->right);
                if(cur->left) stk.push(cur->left);
            }
        }
    }
    
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> leaf_values1, leaf_values2;
        
        build_leaf_values(root1, &leaf_values1);
        build_leaf_values(root2, &leaf_values2);
        
        if(leaf_values1==leaf_values2){
            return true;
        }else{
            return false;
        }
    }
};

/**
Approach 1: Depth First Search
Intuition and Algorithm

Let's find the leaf value sequence for both given trees. 
Afterwards, we can compare them to see if they are equal or not.

To find the leaf value sequence of a tree, we use a depth first search. 
Our dfs function writes the node's value if it is a leaf, and then recursively explores each child. 
This is guaranteed to visit each leaf in left-to-right order, as left-children are fully explored before right-children.

//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Leaf-Similar Trees.
class Solution {
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> leaves1;
        vector<int> leaves2;
        dfs(root1, leaves1);
        dfs(root2, leaves2);

        return leaves1 == leaves2;
    }

    void dfs(TreeNode* node, vector<int>& leaves) {
        if (node == NULL) return;
        if (node->left == NULL && node->right == NULL)
            leaves.push_back(node->val);
        dfs(node->left, leaves);
        dfs(node->right, leaves);
    }
};

Complexity Analysis

Time Complexity: O(T_1 + T_2), where T_1, T_2 are the lengths of the given trees.

Space Complexity: O(T_1 + T_2), the space used in storing the leaf values. 
 
**/

