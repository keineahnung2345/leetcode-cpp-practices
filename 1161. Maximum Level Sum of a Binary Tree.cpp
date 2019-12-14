//Runtime: 248 ms, faster than 15.14% of C++ online submissions for Maximum Level Sum of a Binary Tree.
//Memory Usage: 74.3 MB, less than 100.00% of C++ online submissions for Maximum Level Sum of a Binary Tree.

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
    int maxLevelSum(TreeNode* root) {
        queue<TreeNode*> qNode;
        queue<int> qLevel;
        int maxLevel = 0, maxSum = INT_MIN;
        int lastLevel = 1, lastSum = 0;
        TreeNode* node;
        
        qNode.push(root);
        qLevel.push(lastLevel);
        
        while(!qNode.empty()){
            node = qNode.front();
            // cout << node->val << endl;
            qNode.pop();
            
            lastLevel = qLevel.front();
            qLevel.pop();
            
            lastSum += node->val;
            
            if(node->left){
                qNode.push(node->left);
                qLevel.push(lastLevel+1);
            }
            
            if(node->right){
                qNode.push(node->right);
                qLevel.push(lastLevel+1);
            }
            
            //clean up before entering new level
            if(lastLevel != qLevel.front()){
                if(lastSum > maxSum){
                    maxSum = lastSum;
                    maxLevel = lastLevel;
                }
                lastSum = 0;
            }
        }
        
        return maxLevel;
    }
};
