//BFS
//Runtime: 344 ms, faster than 75.00% of C++ online submissions for Even Odd Tree.
//Memory Usage: 152.7 MB, less than 25.00% of C++ online submissions for Even Odd Tree.
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
    bool isEvenOddTree(TreeNode* root) {
        queue<TreeNode*> q;
        TreeNode* cur;
        int levelId = 0;
        int last;
        
        q.push(root);
        
        while(!q.empty()){
            int levelSize = q.size();
            
            if(!(levelId&1)){
                //even level, increasing
                last = INT_MIN;
            }else{
                last = INT_MAX;
            }
            
            while(levelSize-- > 0){
                cur = q.front(); q.pop();
                
                if(!(levelId&1)){
                    if(!(cur->val&1) || cur->val <= last){
                        return false;
                    }
                }else{
                    if((cur->val&1) || cur->val >= last){
                        return false;
                    }
                }
                last = cur->val;
                
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            
            ++levelId;
        }
        
        return true;
    }
};
