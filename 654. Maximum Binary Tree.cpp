/**
Given an integer array with no duplicates. A maximum tree building on this array is defined as follow:

The root is the maximum number in the array.
The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
Construct the maximum tree by the given array and output the root node of this tree.

Example 1:
Input: [3,2,1,6,0,5]
Output: return the tree root node representing the following tree:

      6
    /   \
   3     5
    \    / 
     2  0   
       \
        1
Note:
The size of the given array will be in the range [1,1000].
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

//Your runtime beats 8.47 % of cpp submissions.
// class Solution {
// public:
//     TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
//         //std::max_element : Returns iterator to the greatest element. From C++11
//         //need to use *max(std::begin(nums), std::end(nums)) to access the greatest element.
//         //max_element(std::begin(nums), std::end(nums)) - std::begin(nums) to get the index of greatest element
//         int maxIndex = max_element(std::begin(nums), std::end(nums)) - std::begin(nums);
//         int max = *max_element(std::begin(nums), std::end(nums)); 
//         // cout << maxIndex << endl;
        
//         TreeNode* root= new TreeNode(max); //new an object an assign its address to a pointer to the object
//         if(nums.begin() < nums.begin()+maxIndex){
//             vector<int> leftnum = vector<int>(nums.begin(), nums.begin()+maxIndex);
//             root->left = constructMaximumBinaryTree(vector<int>(nums.begin(), nums.begin()+maxIndex));
//         }else{
//             root->left = NULL;
//         }
        
//         if(nums.begin()+maxIndex+1 < nums.end()){
//             vector<int> rightnum = vector<int>(nums.begin()+maxIndex+1, nums.end());
//             root->right = constructMaximumBinaryTree(rightnum);
//         }else{
//             root->right = NULL;
//         }
        
//         return root;
//     }
// };

//solution by karanrgoswami
//Your runtime beats 71.37 % of cpp submissions.
/*
Lets break this problem down: 
1.) Find maximum element's index as maxindex
2.) create vector[maxindex] as root return the root.
3.) then run the same function over left subtree and assign the returned output to the left of the first root created (recursion)
4.) then run the same function over rught subtree and assign the returned node to the right of the first root created (recursion)

*/
class Solution {

private: 
    int findMaxIndex(vector<int> &nums, int l, int r)
    {
        int maxI = l;

        for (int i = l; i<=r ; i++)
        {
            if(nums[i] >= nums[maxI])
                maxI = i;               
        }
        return maxI;
    }
    
    TreeNode* constructMaxSubtree(vector<int>& nums, int l, int r)//l, r are inclusive
    {
        if(l>r) return NULL;//not empty when l==r
        int maxI = findMaxIndex(nums, l, r); // this is max index so this nums will be root        
        TreeNode* root = new TreeNode(nums[maxI]);
        //Root is constructed now make children
        root->left = constructMaxSubtree(nums,l,maxI-1);
        root->right = constructMaxSubtree(nums, maxI+1,r);
        return root;
    }
    
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if(nums.size() == 0) return NULL;
        if(nums.size() == 1) return new TreeNode(nums[0]);
        TreeNode *maxTreeRoot;
        maxTreeRoot = constructMaxSubtree(nums,0,(nums.size()-1));
        return maxTreeRoot;
    }
};
