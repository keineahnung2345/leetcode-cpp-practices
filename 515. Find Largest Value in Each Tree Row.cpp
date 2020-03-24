//Runtime: 8 ms, faster than 99.28% of C++ online submissions for Find Largest Value in Each Tree Row.
//Memory Usage: 18.4 MB, less than 100.00% of C++ online submissions for Find Largest Value in Each Tree Row.
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
    vector<int> largestValues(TreeNode* root) {
        if(!root) return vector<int>();
        queue<TreeNode*> q;
        TreeNode* cur;
        vector<int> ans;
        int levelCount = 0, nextLevelCount = 0, levelMax = INT_MIN;
        
        q.push(root);
        levelCount = 1;
        
        while(!q.empty()){
            cur = q.front(); q.pop();
            
            levelMax = max(levelMax, cur->val);
            
            if(cur->left){
                q.push(cur->left);
                nextLevelCount++;
            }
            if(cur->right){
                q.push(cur->right);
                nextLevelCount++;
            }
            
            levelCount--;
            if(levelCount == 0){
                ans.push_back(levelMax);
                levelCount = nextLevelCount;
                nextLevelCount = 0;
                levelMax = INT_MIN;
            }
        }
        
        return ans;
    }
};
