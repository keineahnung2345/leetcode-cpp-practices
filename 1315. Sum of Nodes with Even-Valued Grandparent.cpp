//Hint 1 : Traverse the tree keeping the parent and the grandparent.
//Hint 2 : If the grandparent of the current node is even-valued, add the value of this node to the answer.

/*
Runtime: 56 ms, faster than 25.02% of C++ online submissions for Sum of Nodes with Even-Valued Grandparent.
Memory Usage: 31.5 MB, less than 100.00% of C++ online submissions for Sum of Nodes with Even-Valued Grandparent.
*/

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
    int sumEvenGrandparent(TreeNode* root) {
        std::stack<TreeNode*> stk;
        std::stack<int> parents, grandparents;
        int parent, grandparent;
        TreeNode *node;
        int ans = 0;
        
        stk.push(root);
        //The value of nodes is between 1 and 100.
        parents.push(0);
        grandparents.push(0);
        
        while(!stk.empty()){
            node = stk.top(); stk.pop();
            parent = parents.top(); parents.pop();
            grandparent = grandparents.top(); grandparents.pop();
            
            if(grandparent != 0 && grandparent % 2 == 0){
                ans += node->val;
            }
            
            if(node->right){
                stk.push(node->right);
                parents.push(node->val);
                //current node's parent is its child's grandparent
                grandparents.push(parent);
            }
            
            if(node->left){
                stk.push(node->left);
                parents.push(node->val);
                //current node's parent is its child's grandparent
                grandparents.push(parent);
            }
        }
        
        return ans;
    }
};
