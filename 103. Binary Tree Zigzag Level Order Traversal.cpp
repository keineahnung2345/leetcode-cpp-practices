//stack
//Runtime: 8 ms, faster than 36.00% of C++ online submissions for Binary Tree Zigzag Level Order Traversal.
//Memory Usage: 12.3 MB, less than 54.30% of C++ online submissions for Binary Tree Zigzag Level Order Traversal.
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        
        if(!root) return ans;
        
        stack<TreeNode*> stk, stk_next;
        TreeNode* cur;
        bool pos = true;
        
        stk.push(root);
        while(!stk.empty()){
            int levelSize = stk.size();
            vector<int> level(levelSize);
            bool next_pos = !pos;
            
            for(int i = 0; i < levelSize; ++i){
                cur = stk.top(); stk.pop();
                level[i] = cur->val;
                
                TreeNode* child1 = cur->left;
                TreeNode* child2 = cur->right;
                
                if(next_pos){
                    /*
                    if next_pos is true, we go from left to right,
                    so right child should be pushed into stack earlier
                    */
                    swap(child1, child2);
                }
                
                if(child1) stk_next.push(child1);
                if(child2) stk_next.push(child2);
                
            }
            
            swap(stk, stk_next);
            pos = next_pos;
            ans.push_back(level);
        }
        
        return ans;
    }
};
