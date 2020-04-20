//Runtime: 4 ms, faster than 83.62% of C++ online submissions for Construct Binary Search Tree from Preorder Traversal.
//Memory Usage: 8.9 MB, less than 100.00% of C++ online submissions for Construct Binary Search Tree from Preorder Traversal.

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
    
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        if(preorder.size() == 0) return NULL;
        TreeNode *root, *pre, *cur;
        root = new TreeNode(preorder[0]);
        
        for(int i = 1; i < preorder.size(); i++){
            int p = preorder[i];
            cur = root;
            while(cur){
                pre = cur;
                if(p < cur->val){
                    cur = cur->left;
                }else if(p >= cur->val){
                    cur = cur->right;
                }
            }
            if(p < pre->val){
                pre->left = new TreeNode(p);
            }else if(p >= pre->val){
                pre->right = new TreeNode(p);
            }
        }
        return root;
    }
};

//Recursive
//Runtime: 4 ms, faster than 86.93% of C++ online submissions for Construct Binary Search Tree from Preorder Traversal.
//Memory Usage: 11.6 MB, less than 28.57% of C++ online submissions for Construct Binary Search Tree from Preorder Traversal.
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
    TreeNode* rbstFromPreorder(vector<int>& preorder, int l, int r){
        // cout << l << " " << r << endl;
        if(l > r) return nullptr;
        //[l, r]: inclusive
        TreeNode* node = new TreeNode(preorder[l]);
        
        //the smallest number > x
        auto it = upper_bound(preorder.begin()+l+1, preorder.begin()+r+1, preorder[l]);
        
        node->left = rbstFromPreorder(preorder, l+1, it-preorder.begin()-1);
        node->right = rbstFromPreorder(preorder, it-preorder.begin(), r);
        
        return node;
    };
    
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return rbstFromPreorder(preorder, 0, preorder.size()-1);
    }
};
