//binary tree inorder traversal using stack
//https://github.com/keineahnung2345/leetcode-cpp-practices/blob/master/94.%20Binary%20Tree%20Inorder%20Traversal.cpp#L126
//Runtime: 56 ms, faster than 98.62% of C++ online submissions for Binary Search Tree Iterator.
//Memory Usage: 27.8 MB, less than 10.86% of C++ online submissions for Binary Search Tree Iterator.
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
class BSTIterator {
public:
    stack<TreeNode*> stk;
    TreeNode* cur;
    
    BSTIterator(TreeNode* root) {
        cur = root;
    }
    
    /** @return the next smallest number */
    int next() {
        while(cur){
            stk.push(cur);
            cur = cur->left;
        }
        cur = stk.top(); stk.pop();
        int val = cur->val;
        cur = cur->right;
        return val;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return cur || !stk.empty();
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
 
