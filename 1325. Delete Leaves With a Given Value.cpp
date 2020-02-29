//Runtime: 32 ms, faster than 13.93% of C++ online submissions for Delete Leaves With a Given Value.
//Memory Usage: 27 MB, less than 100.00% of C++ online submissions for Delete Leaves With a Given Value.

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
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        stack<TreeNode*> stk;
        bool changed = false;
        //bool: whether the child is left
        map<TreeNode*, pair<bool, TreeNode*>> parent;
        TreeNode* cur;
        
        do{
            parent.clear();
            changed = false;
            
            stk.push(root);
            parent[root] = make_pair(false, nullptr);

            while(!stk.empty()){
                cur = stk.top(); stk.pop();

                //post-order
                if(cur->right){
                    stk.push(cur->right);
                    parent[cur->right] = make_pair(false, cur);
                }
                if(cur->left){
                    stk.push(cur->left);
                    parent[cur->left] = make_pair(true, cur);
                }

                if(!cur->left && !cur->right && cur->val == target){
                    if(parent[cur].second == nullptr){
                        //cur node is root
                        return nullptr;
                    }
                    //cur node is not root
                    if(parent[cur].first){
                        parent[cur].second->left = nullptr;
                    }else{
                        parent[cur].second->right = nullptr;
                    }
                    changed = true;
                }

            }
            
        }while(changed);
        
        return root;
    }
};

//Recursion Solution
//https://leetcode.com/problems/delete-leaves-with-a-given-value/discuss/484264/JavaC%2B%2BPython-Recursion-Solution
//Runtime: 20 ms, faster than 85.19% of C++ online submissions for Delete Leaves With a Given Value.
//Memory Usage: 20.5 MB, less than 100.00% of C++ online submissions for Delete Leaves With a Given Value.
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
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        if(root->left) root->left = removeLeafNodes(root->left, target);
        if(root->right) root->right = removeLeafNodes(root->right, target);
        //root->left can only be same as root->right when they are both nullptr
        return (root->left == root->right) && (root->val == target) ? nullptr : root;
    }
};
