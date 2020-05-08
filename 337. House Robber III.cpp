//Runtime: 28 ms, faster than 34.86% of C++ online submissions for House Robber III.
//Memory Usage: 25.1 MB, less than 16.67% of C++ online submissions for House Robber III.
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
    unordered_map<TreeNode*, int> memo;
    
    int rob(TreeNode* root) {
        if(root == nullptr) return 0;
        if(memo.find(root) != memo.end()) return memo[root];
        
        int robHere = root->val;
        if(root->left) robHere += rob(root->left->left) + rob(root->left->right);
        if(root->right) robHere += rob(root->right->left) + rob(root->right->right);
        
        int robNext = rob(root->left) + rob(root->right);
        
        memo[root] = max(robHere, robNext);
        return memo[root];
    }
};

//dfs without memo
//https://github.com/keineahnung2345/fucking-algorithm/blob/note/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E7%B3%BB%E5%88%97/%E6%8A%A2%E6%88%BF%E5%AD%90.md
//Runtime: 32 ms, faster than 26.22% of C++ online submissions for House Robber III.
//Memory Usage: 32.5 MB, less than 5.55% of C++ online submissions for House Robber III.
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
    vector<int> dfs(TreeNode* node){
        if(node == nullptr) return {0,0};
        
        /*
        a vector of two elements,
        first is the money if robe here,
        second is the money if robe its next
        */
        vector<int> left = dfs(node->left);
        vector<int> right = dfs(node->right);
        
        /*
        left[1]:
        dfs(node->left)[1] :
        max(preLeft[0], preLeft[1]) + max(preRight[0], preRight[1]) : 
        maxValueOf(dfs(node->left->left)) + maxValueOf(dfs(node->left->right)) :
        robInPrevMethod(node->left->left) + robInPrevMethod(node->left->right)
        */
        int robHere = node->val + left[1] + right[1];
        
        /*
        why not:
        int robNext = left[0] + right[0];
        ?
        
        in the last method:
        int robNext = rob(root->left) + rob(root->right);
        return max(robHere, robNext);
        the return value of rob() function is the max of robHere and robNext,
        but in current method, we don't take max() before dfs() return.
        So here we need to take max of left and right to 
        mimic what the last method does
        */
        int robNext = max(left[0], left[1]) + max(right[0], right[1]);
        
        return {robHere, robNext};
    };
    
    int rob(TreeNode* root) {
        bool dummy = false;
        vector<int> v = dfs(root);
        return max(v[0], v[1]);
    }
};
