//naive
//Approach 1: Flattening the BST
//Runtime: 60 ms, faster than 95.83% of C++ online submissions for Binary Search Tree Iterator.
//Memory Usage: 29.2 MB, less than 10.86% of C++ online submissions for Binary Search Tree Iterator.
//time: O(N), space: O(N)
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
    vector<int> values;
    int pos;
    
    void inorder(TreeNode* node){
        if(!node) return;
        inorder(node->left);
        values.push_back(node->val);
        inorder(node->right);
    }
    
    BSTIterator(TreeNode* root) {
        inorder(root);
        pos = 0;
    }
    
    /** @return the next smallest number */
    int next() {
        return values[pos++];
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return pos < values.size();
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

//binary tree inorder traversal using stack
//https://github.com/keineahnung2345/leetcode-cpp-practices/blob/master/94.%20Binary%20Tree%20Inorder%20Traversal.cpp#L126
//Runtime: 56 ms, faster than 98.62% of C++ online submissions for Binary Search Tree Iterator.
//Memory Usage: 27.8 MB, less than 10.86% of C++ online submissions for Binary Search Tree Iterator.
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
 
