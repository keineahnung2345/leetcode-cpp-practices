//Runtime: 8 ms, faster than 100.00% of C++ online submissions for Symmetric Tree.
//Memory Usage: 14.9 MB, less than 99.64% of C++ online submissions for Symmetric Tree.

//iterative
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
    bool isLevelSymmetric(vector<int>& level){
        if(level.size() == 1) return true;
        
        //besides root, each level's size should be even
        for(int i = 0; i < level.size()/2; i++){
            if(level[i] != level[level.size()-1-i]) return false;
        }
        
        return true;
    }
    bool isSymmetric(TreeNode* root) {
        queue<TreeNode*> q;
        TreeNode* cur;
        int levelCount = 0;
        vector<int> level;
        
        q.push(root);
        levelCount = 1;
        
        while(!q.empty()){
            cur = q.front();
            q.pop();
            if(cur != NULL) level.push_back(cur->val);
            else level.push_back(INT_MIN);
            
            levelCount--;
            
            //we should also consider null node because it affect tree structure
            if(cur != NULL){
                q.push(cur->left);
                q.push(cur->right);
            }
            
            if(levelCount == 0){
                if(!isLevelSymmetric(level)) return false;
                levelCount = q.size();
                level.clear();
            }
        }
        
        return true;
    }
};

/**
Approach 1: Recursive
**/

/**
Complexity Analysis

Time complexity : O(n)O(n). Because we traverse the entire input tree once, the total run time is O(n)O(n), where nn is the total number of nodes in the tree.

Space complexity : The number of recursive calls is bound by the height of the tree. In the worst case, the tree is linear and the height is in O(n)O(n). Therefore, space complexity due to recursive calls on the stack is O(n)O(n) in the worst case. 
**/

//Runtime: 16 ms, faster than 32.96% of C++ online submissions for Symmetric Tree.
//Memory Usage: 14.6 MB, less than 100.00% of C++ online submissions for Symmetric Tree.

/**
class Solution {
public:
    bool isMirror(TreeNode* t1, TreeNode* t2){
        if(t1 == NULL && t2 == NULL) return true;
        //one of it is NULL
        if(t1 == NULL || t2 == NULL) return false;
        //both are not NULL
        return (t1->val == t2->val) &&
            isMirror(t1->left, t2->right) && 
            isMirror(t1->right, t2->left);
    }
    bool isSymmetric(TreeNode* root) {
        return isMirror(root, root);
    }
};
**/

/**
Approach 2: Iterative
**/

/**
Complexity Analysis

Time complexity : O(n)O(n). Because we traverse the entire input tree once, the total run time is O(n)O(n), where nn is the total number of nodes in the tree.

Space complexity : There is additional space required for the search queue. In the worst case, we have to insert O(n)O(n) nodes in the queue. Therefore, space complexity is O(n)O(n).
**/

/**
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        queue<TreeNode*> q;
        TreeNode *t1, *t2;
        
        q.push(root);
        q.push(root);
        
        while(!q.empty()){
            t1 = q.front(); q.pop();
            t2 = q.front(); q.pop();
            if(t1 == NULL && t2 == NULL) continue;
            if(t1 == NULL || t2 == NULL) return false;
            if(t1->val != t2->val) return false;
            q.push(t1->left);
            q.push(t2->right);
            q.push(t1->right);
            q.push(t2->left);
        }
        
        return true;
    }
};
**/
