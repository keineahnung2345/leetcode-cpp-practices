//Runtime: 8 ms, faster than 30.69% of C++ online submissions for Sum Root to Leaf Numbers.
//Memory Usage: 12.4 MB, less than 85.67% of C++ online submissions for Sum Root to Leaf Numbers.
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int sumNumbers(TreeNode* root, int initVal = 0) {
        if(root == nullptr) return 0;
        if(root->left == nullptr && root->right == nullptr){
            //leaf node
            return initVal + root->val;
        }
        
        //non-leaf node
        //accumulate the score from left and right subtrees
        int sum = 0;
        sum += sumNumbers(root->left, (initVal+root->val)*10) + sumNumbers(root->right, (initVal+root->val)*10);
        
        return sum;
    }
};
