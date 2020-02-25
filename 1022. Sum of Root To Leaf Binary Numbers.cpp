//Runtime: 4 ms, faster than 95.02% of C++ online submissions for Sum of Root To Leaf Binary Numbers.
//Memory Usage: 17.5 MB, less than 20.00% of C++ online submissions for Sum of Root To Leaf Binary Numbers.

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
    int sumRootToLeaf(TreeNode* root) {
        int sum = 0;
        stack<TreeNode*> stk;
        TreeNode* cur;
        map<TreeNode*, TreeNode*> parent;
        
        stk.push(root);
        parent[root] = nullptr;
        
        while(!stk.empty()){
            cur = stk.top(); stk.pop();
            if(!cur->left && !cur->right){
                int path_val = 0, h = 0 ;
                while(cur != nullptr){
                    path_val += (cur->val << h);
                    h++;
                    cur = parent[cur];
                }
                // cout << path_val << endl;
                sum += path_val;
                continue;
            }
            if(cur->right){
                stk.push(cur->right);
                parent[cur->right] = cur;
            }
            if(cur->left){
                stk.push(cur->left);
                parent[cur->left] = cur;
            }
        }
        
        return sum;
    }
};
