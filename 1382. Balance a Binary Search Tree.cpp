//Runtime: 188 ms
//Memory Usage: 52 MB
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
    void inOrder(TreeNode* node, vector<int>& nums){
        if(!node)return;
        inOrder(node->left, nums);
        nums.push_back(node->val);
        inOrder(node->right, nums);
    }
    
    TreeNode* buildTree(vector<int>& nums, int start, int end){
        //end is inclusive
        if(start > end) return NULL;
        int mid = (start+end)/2;
        TreeNode* newroot = new TreeNode(nums[mid]);
        newroot->left = buildTree(nums, start, mid-1);
        newroot->right = buildTree(nums, mid+1, end);
        return newroot;
    }
    
    TreeNode* balanceBST(TreeNode* root) {
        //parse tree
        vector<int> nums;
        inOrder(root, nums);
        
        // for(int e : nums){
        //     cout << e << " ";
        // }
        // cout << endl;
        
        //build tree
        int N = nums.size();
        TreeNode* newroot = new TreeNode(nums[N/2]);
        newroot->left = buildTree(nums, 0, N/2-1);
        newroot->right = buildTree(nums, N/2+1, N-1);
        
        return newroot;
    }
};
