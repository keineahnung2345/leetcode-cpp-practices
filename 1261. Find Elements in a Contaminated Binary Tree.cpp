//Runtime: 888 ms, faster than 9.56% of C++ online submissions for Find Elements in a Contaminated Binary Tree.
//Memory Usage: 17.7 MB, less than 100.00% of C++ online submissions for Find Elements in a Contaminated Binary Tree.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class FindElements {
public:
    TreeNode* myroot;
    
    TreeNode* _FindElements(TreeNode* node, int v){
        //preorder
        node->val = v;
        if(node->left) _FindElements(node->left, v*2+1);
        if(node->right) _FindElements(node->right, v*2+2);
        return node;
    };
    
    FindElements(TreeNode* root) {
        myroot = _FindElements(root, 0);
    }
    
    bool _find(int target, TreeNode* node){
        //preorder traversal
        if(target == node->val) return true;
        bool found = false;
        //if find in one of its children, then that's found
        if(node->left) found = found | _find(target, node->left);
        if(node->right) found = found | _find(target, node->right);
        return found;
    }
    
    bool find(int target) {
        if(!myroot) return false;
        //traverse the whole tree
        return _find(target, myroot);
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
 
