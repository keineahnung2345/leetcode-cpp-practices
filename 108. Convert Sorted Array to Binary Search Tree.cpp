/**
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example:

Given the sorted array: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
**/

//Runtime: 24 ms, faster than 85.84% of C++ online submissions for Convert Sorted Array to Binary Search Tree.
//Memory Usage: 21.2 MB, less than 46.88% of C++ online submissions for Convert Sorted Array to Binary Search Tree.

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
    TreeNode* buildTree(vector<int>& nums, int start, int end){
        //end + 1 - start : the length of subarray
        if(end + 1 - start < 1) return NULL;
        int mid = (start+end)/2;
        //https://stackoverflow.com/questions/5914422/proper-way-to-initialize-c-structs
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = buildTree(nums, start, mid-1);
        root->right = buildTree(nums, mid+1, end);
        return root;
    }
    
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if(nums.size() == 0) return NULL;
        TreeNode* root = buildTree(nums, 0, nums.size()-1);
        return root;
    }
};
