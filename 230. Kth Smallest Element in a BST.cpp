//Runtime: 16 ms, faster than 96.43% of C++ online submissions for Kth Smallest Element in a BST.
//Memory Usage: 20.9 MB, less than 100.00% of C++ online submissions for Kth Smallest Element in a BST.

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
    int k;
    
    int inOrder(TreeNode* node){
        if(!node) return -1;
        int lval = inOrder(node->left);
        if(lval != -1) return lval;
        if(--k == 0){
            return node->val;
        }
        int rval = inOrder(node->right);
        if(rval != -1) return rval;
        return -1;
    };
    
    int kthSmallest(TreeNode* root, int k) {
        this->k = k;
        return inOrder(root);
    }
};

//Approach 2: Iteration
//Runtime: 24 ms, faster than 51.38% of C++ online submissions for Kth Smallest Element in a BST.
//Memory Usage: 20.7 MB, less than 100.00% of C++ online submissions for Kth Smallest Element in a BST.
//time: O(H+k), space: O(H+k), where H is the height of the tree, it could be N or logN
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
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> stk;
        TreeNode* cur = root;
        
        do{
            while(cur){
                stk.push(cur);
                cur = cur->left;
            }

            cur = stk.top(); stk.pop();

            if(--k == 0) return cur->val;
            // cout << cur->val << " ";
            cur = cur->right;
            
        //when stk not empty or cur not null, we should continue the loop
        }while(!stk.empty() || cur);
        // cout << endl;
        
        return -1;
    }
};
