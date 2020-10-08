//Naive, only compare with its left and right children
//WA: 70 / 75 test cases passed.
//[10,5,15,null,null,6,20]
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if(!root) return true;
        if(root->left && root->left->val >= root->val) return false;
        if(root->right && root->right->val <= root->val) return false;
        
        return isValidBST(root->left) && isValidBST(root->right);
    }
};

//Recursion
//Runtime: 8 ms, faster than 99.49% of C++ online submissions for Validate Binary Search Tree.
//Memory Usage: 22.2 MB, less than 5.05% of C++ online submissions for Validate Binary Search Tree.
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
    bool isValidBST(TreeNode* root, int& minv, int& maxv) {
        if(!root) return true;
        if(!root->left && !root->right){
            minv = maxv = root->val;
            return true;
        }else if(root->left && root->right){
            int minl = INT_MAX, maxl = INT_MIN;
            //if subtree is invalid, return immediately!!
            if(!isValidBST(root->left, minl, maxl)) return false;
            if(maxl >= root->val) return false;
            
            int minr = INT_MAX, maxr = INT_MIN;
            if(!isValidBST(root->right, minr, maxr)) return false;
            if(minr <= root->val) return false;
            
            minv = minl;
            maxv = maxr;
            
            return true;
        }else if(!root->right){
            //left subtree is not empty
            int minl = INT_MAX, maxl = INT_MIN;
            if(!isValidBST(root->left, minl, maxl)) return false;
            if(maxl >= root->val) return false;
            maxv = root->val;
            minv = minl;
            return true;
        }else/* if(!root->left)*/{
            //right subtree is not empty
            int minr = INT_MAX, maxr = INT_MIN;
            if(!isValidBST(root->right, minr, maxr)) return false;
            if(minr <= root->val) return false;
            minv = root->val;
            maxv = maxr;
            return true;
        }
    }
    
    bool isValidBST(TreeNode* root) {
        int rootmin = INT_MAX, rootmax = INT_MIN;
        return isValidBST(root, rootmin, rootmax);
    }
};

//Approach 1: Recursion(cleaner)
//Runtime: 16 ms, faster than 82.11% of C++ online submissions for Validate Binary Search Tree.
//Memory Usage: 22 MB, less than 15.55% of C++ online submissions for Validate Binary Search Tree.
//time: O(N), space: O(N)
class Solution {
public:
    bool recurse(TreeNode* node, long long lower, long long upper){
        if(!node) return true;
        
        if(node->val <= lower) return false;
        if(node->val >= upper) return false;
        
        if(!recurse(node->left, lower, node->val)) return false;
        if(!recurse(node->right, node->val, upper)) return false;
        
        return true;
    }
    
    bool isValidBST(TreeNode* root) {
        // cout << LLONG_MIN << endl;
        // cout << LLONG_MAX << endl;
        return recurse(root, LLONG_MIN, LLONG_MAX);
    }
};

//Approach 2: Iteration
//Runtime: 20 ms, faster than 56.08% of C++ online submissions for Validate Binary Search Tree.
//Memory Usage: 22.2 MB, less than 5.05% of C++ online submissions for Validate Binary Search Tree.
//time: O(N), space: O(N)
class Solution {
public:
    typedef tuple<TreeNode*, long long, long long> tpnlu;
    bool isValidBST(TreeNode* root) {
        stack<tpnlu> stk;
        
        stk.push({root, LLONG_MIN, LLONG_MAX});
        
        while(!stk.empty()){
            tpnlu tp = stk.top(); stk.pop();
            TreeNode* node = get<0>(tp);
            long long lower = get<1>(tp);
            long long upper = get<2>(tp);
            
            if(node == nullptr) continue;
            
            // cout << lower << ", " << node->val << ", " << upper << endl;
            if(node->val <= lower) return false;
            if(node->val >= upper) return false;
            
            stk.push({node->left, lower, node->val});
            stk.push({node->right, node->val, upper});
        }
        
        return true;
    }
};

//Approach 3: Inorder traversal(recursive)
//Runtime: 20 ms, faster than 56.08% of C++ online submissions for Validate Binary Search Tree.
//Memory Usage: 22 MB, less than 12.60% of C++ online submissions for Validate Binary Search Tree.
//time: O(N), space: O(N)
class Solution {
public:
    bool inOrder(TreeNode* node, long long& last){
        if(!node) return true;
        if(!inOrder(node->left, last)) return false;
        // cout << node->val << " " << last << endl;
        
        //check for current node
        if(node->val <= last) return false;
        //update last for its right child and also its parent to its right
        /*
        if current node is left child, 
        when it returns to its parent(to its right),
        "last" will be updated to the max value in that parent's left subtree,
        then parent's val will be compared with "last"
        
        if current node is right child,
        it will return to one of its ancestor to the right
        */
        last = node->val;
        
        if(!inOrder(node->right, last)) return false;
        return true;
    }
    
    bool isValidBST(TreeNode* root) {
        long long last = LLONG_MIN;
        return inOrder(root, last);
    }
};

//Inorder traversal(iterative)
//Runtime: 16 ms, faster than 82.11% of C++ online submissions for Validate Binary Search Tree.
//Memory Usage: 22.1 MB, less than 7.55% of C++ online submissions for Validate Binary Search Tree.
//time: O(N), space: O(N)
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> stk;
        
        long long last = LLONG_MIN;
        TreeNode* cur = root;
        
        while(!stk.empty() || cur){
            while(cur){
                stk.push(cur);
                cur = cur->left;
            }
            
            cur = stk.top(); stk.pop();
            
            if(cur->val <= last) return false;
            last = cur->val;
            
            cur = cur->right;
        }
        
        return true;
    }
};
