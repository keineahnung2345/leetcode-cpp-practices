//bfs, level-wise
//Runtime: 4 ms, faster than 97.63% of C++ online submissions for Maximum Width of Binary Tree.
//Memory Usage: 15.7 MB, less than 83.60% of C++ online submissions for Maximum Width of Binary Tree.
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
    int widthOfBinaryTree(TreeNode* root) {
        if(root == nullptr) return 0;
        
        int ans = 0;
        
        queue<pair<TreeNode*, int>> q;
        
        q.push({root, 0});
        
        while(!q.empty()){
            int levelSize = q.size();
            
            int firstId = q.front().second;
            int id = firstId;
            
            while(levelSize-- > 0){
                pair<TreeNode*, int> curP = q.front(); q.pop();
                TreeNode* cur = curP.first;
                id = curP.second;
                
                if(cur->left){
                    // - firstId*2: to avoid overflow
                    q.push({cur->left, id*2 - firstId*2});
                }
                
                if(cur->right){
                    q.push({cur->right, id*2 + 1 - firstId*2});
                }
            }
            
            ans = max(ans, id - firstId + 1);
        }
        
        return ans;
    }
};
