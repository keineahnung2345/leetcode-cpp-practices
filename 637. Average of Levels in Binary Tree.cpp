/**
Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.
Example 1:
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
Note:
The range of node's value is in the range of 32-bit signed integer.
**/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 //Runtime: 24 ms, faster than 99.44% of C++ online submissions for Average of Levels in Binary Tree.
//Memory Usage: 22.3 MB, less than 25.66% of C++ online submissions for Average of Levels in Binary Tree.
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> ans;
        queue<TreeNode*> q;
        vector<int> levelVals;
        int level = 0, levelCount = 1, nextLevelCount = 0;
        
        q.push(root);
        
        while(q.size()!=0){
            TreeNode* cur = q.front();
            q.pop();
            
            levelVals.push_back(cur->val);
            
            levelCount--;
            
            if(cur->left!=NULL){
                q.push(cur->left);
                nextLevelCount++;
            }
            
            if(cur->right!=NULL){
                q.push(cur->right);
                nextLevelCount++;
            }
            
            if(levelCount==0){
                levelCount = nextLevelCount;
                nextLevelCount = 0;
                level++;
                double levelSum = accumulate(levelVals.begin(), levelVals.end(), 0.0);
                ans.push_back(levelSum/levelVals.size());
                levelVals.clear();
            }
        }
        
        return ans;
    }
};
