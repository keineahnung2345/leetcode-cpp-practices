//Runtime: 28 ms, faster than 75.28% of C++ online submissions for Path Sum III.
//Memory Usage: 14.8 MB, less than 100.00% of C++ online submissions for Path Sum III.

https://leetcode.com/problems/path-sum-iii/discuss/91889/Simple-Java-DFS
/**
Typical recursive DFS.
Space: O(n) due to recursion.
Time: O(n^2) in worst case (no branching); O(nlogn) in best case (balanced tree).
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
class Solution {
public:
    int pathSumFrom(TreeNode* root, int sum){
        if(!root) return 0;
        return (int)(root->val == sum) +
            pathSumFrom(root->left, sum - root->val) + 
            pathSumFrom(root->right, sum - root->val);
    }
    int pathSum(TreeNode* root, int sum) {
        if(!root) return 0;
        return pathSumFrom(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
    }
};
