//Runtime: 56 ms, faster than 23.77% of C++ online submissions for Construct Binary Tree from Inorder and Postorder Traversal.
//Memory Usage: 24.2 MB, less than 29.37% of C++ online submissions for Construct Binary Tree from Inorder and Postorder Traversal.
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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder, int is = -1, int ie = -1, int ps = -1, int pe = -1) {
        if(is > ie || ps > pe) return nullptr;
        
        int n = inorder.size();
        
        if(n == 0) return nullptr;
        
        if(is == -1){
            is = ps= 0;
            ie = pe = n-1;
        }
        
        TreeNode* node = new TreeNode(postorder[pe]);
        
        int iroot = find(inorder.begin(), inorder.end(), postorder[pe]) - inorder.begin();
        // cout << "inorder's root at: " << iroot << endl;
        int leftSize = iroot-is;
        
        node->left = buildTree(inorder, postorder, is, iroot-1, ps, ps+leftSize-1);
        node->right = buildTree(inorder, postorder, iroot+1, ie, ps+leftSize, pe-1);
        
        return node;
    }
};

//Use HashMap so we don't need to "find"
//https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/discuss/34782/My-recursive-Java-code-with-O(n)-time-and-O(n)-space
//Runtime: 24 ms, faster than 74.28% of C++ online submissions for Construct Binary Tree from Inorder and Postorder Traversal.
//Memory Usage: 24 MB, less than 36.01% of C++ online submissions for Construct Binary Tree from Inorder and Postorder Traversal.
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
    unordered_map<int, int> val2idx;
    
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder, int is, int ie, int ps, int pe) {
        if(is > ie || ps > pe) return nullptr;
        
        TreeNode* node = new TreeNode(postorder[pe]);
        
        int iroot = val2idx[postorder[pe]];
        // cout << "inorder's root at: " << iroot << endl;
        int leftSize = iroot-is;
        
        node->left = buildTree(inorder, postorder, is, iroot-1, ps, ps+leftSize-1);
        node->right = buildTree(inorder, postorder, iroot+1, ie, ps+leftSize, pe-1);
        
        return node;
    };
    
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        
        if(n == 0) return nullptr;
        
        for(int i = 0; i < n; ++i){
            val2idx[inorder[i]] = i;
        }
        
        return buildTree(inorder, postorder, 0, n-1, 0, n-1);
    }
};
