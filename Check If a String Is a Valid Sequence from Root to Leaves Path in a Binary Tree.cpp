//backtracking
//Runtime: 92 ms
//Memory Usage: 49 MB
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
enum class COMP_RES{
    SAME,
    //used when path is not complete but path is equal to former path of arr
    NOT_DIFF,
    DIFF
};

class Solution {
public:
    vector<int> arr;
    
    COMP_RES isValid(vector<int>& path){
        //check if path equals to path
        //this can be used by incomplete path
        if(path.size() > arr.size()) return COMP_RES::DIFF;
        for(int i = 0; i < path.size(); i++){
            if(arr[i] != path[i]) return COMP_RES::DIFF;
        }
        //return NOT_DIFF when path is equal to former part of arr
        return (path.size() == arr.size()) ? COMP_RES::SAME : COMP_RES::NOT_DIFF;
    }
    
    COMP_RES backtrack(TreeNode* node, vector<int>& path){
        if(!node->left && !node->right){
            //leaf node
            return isValid(path);
        }else if(path.size() >= arr.size()){
            //early stopping
            return COMP_RES::DIFF;
        }
        
        COMP_RES res = isValid(path);
        if(res == COMP_RES::DIFF || res == COMP_RES::SAME) return res;
        //now res is COMP_RES::NOT_DIFF
        //if former part of path is equal to that of arr
        //continue to search and append path
        res = COMP_RES::DIFF;
        if(node->left){
            path.push_back(node->left->val);
            res = backtrack(node->left, path);
            if(res == COMP_RES::SAME) return COMP_RES::SAME;
            path.pop_back();
        }
        if(node->right){
            path.push_back(node->right->val);
            res = backtrack(node->right, path);
            if(res == COMP_RES::SAME) return COMP_RES::SAME;
            path.pop_back();
        }
        
        //neither of its children match arr
        return COMP_RES::DIFF;
    };
    
    bool isValidSequence(TreeNode* root, vector<int>& arr) {
        if(!root) return false;
        this->arr = arr;
        vector<int> path = {root->val};
        return backtrack(root, path) == COMP_RES::SAME;
    }
};

//recursive
//https://leetcode.com/explore/featured/card/30-day-leetcoding-challenge/532/week-5/3315/discuss/604349/CPP-SIMPLE-EASY-DFS-SOLUTION-WITH-COMMENTS
//Runtime: 96 ms
//Memory Usage: 48.9 MB
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
    bool isValidSequence(TreeNode* root, vector<int>& arr, int i = 0) {
        if(i <= arr.size() && !root){
            return false;
        }
        //stop when i is equal to arr.size()-1
        if(i == arr.size()-1){
            //check if its leaf
            return root->val == arr[i] && !root->left && !root->right;
        }
        //continue to increase i
        return root->val == arr[i] && (isValidSequence(root->left, arr, i+1) || isValidSequence(root->right, arr, i+1));
    }
};
