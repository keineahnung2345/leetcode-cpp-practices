//Runtime: 56 ms, faster than 20.38% of C++ online submissions for Recover Binary Search Tree.
//Memory Usage: 55.2 MB, less than 5.06% of C++ online submissions for Recover Binary Search Tree.
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
    vector<TreeNode*> nodes;
    vector<int> vals;
    
    void inorder(TreeNode* node){
        if(!node) return;
        inorder(node->left);
        nodes.push_back(node);
        vals.push_back(node->val);
        inorder(node->right);
    }
    
    void inorder_revise(TreeNode* node, int& order, vector<int>& indices_to_revise, vector<int>& vals_to_revise){
        if(!node) return;
        inorder_revise(node->left, order, indices_to_revise, vals_to_revise);
        auto it = find(indices_to_revise.begin(), indices_to_revise.end(), order);
        if(it != indices_to_revise.end()){
            // cout << "revise " << node->val << " to " << vals_to_revise[it-indices_to_revise.begin()] << endl;
            node->val = vals_to_revise[it-indices_to_revise.begin()];
        }
        ++order;
        inorder_revise(node->right, order, indices_to_revise, vals_to_revise);
    }
    
    void recoverTree(TreeNode* root) {
        inorder(root);
        
        //the values in right order
        sort(vals.begin(), vals.end());
        
        vector<int> indices_to_revise;
        vector<int> vals_to_revise;
        for(int i = 0; i < nodes.size(); ++i){
            //the node's value isn't the value it should be
            if(nodes[i]->val != vals[i]){
                indices_to_revise.push_back(i);
                vals_to_revise.push_back(vals[i]);
            }
        }
        
        int order = 0;
        inorder_revise(root, order, indices_to_revise, vals_to_revise);
    }
};

//Morris Traversal, threaded binary tree
//https://leetcode.com/problems/recover-binary-search-tree/discuss/32559/Detail-Explain-about-How-Morris-Traversal-Finds-two-Incorrect-Pointer
//Runtime: 48 ms, faster than 33.92% of C++ online submissions for Recover Binary Search Tree.
//Memory Usage: 53.7 MB, less than 33.72% of C++ online submissions for Recover Binary Search Tree.
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
    TreeNode *cur, *prev;
    TreeNode *first, *second;
    
    void doWork(){
        //do work related to this problem
        if(prev != nullptr && prev->val > cur->val){
            if(first == nullptr){
                first = prev;
                // cout << "first: " << prev->val << endl;
            }
            /*
            also set second when first == nullptr,
            this is so deal with the case that 
            first and second may be consecutive
            */
            second = cur;
            // cout << "second: " << cur->val << endl;
        }
        //maintain the "prev" pointer
        prev = cur;
    };
    
    void recoverTree(TreeNode* root) {
        cur = root;
        prev = nullptr;
        first = second = nullptr;
        
        //the framework is Morris traversal
        while(cur){
            if(cur->left){
                //find its predecessor in its left subtree
                TreeNode* pred = cur->left;
                while(pred->right != nullptr && pred->right != cur){
                    pred = pred->right;
                }
                
                if(pred->right == nullptr){
                    /*
                    connect the predecessor's right to cur,
                    so we can come back to cur later
                   */
                    pred->right = cur;
                    /*
                    now that it is ensured that we can go back to cur later,
                    we can go to its left subtree safely
                    */
                    cur = cur->left;
                }else{
                    //here pred->right == cur
                    
                    doWork();
                    // cout << cur->val << endl;
                    
                    pred->right = nullptr;
                    /*
                    we have visit cur's left subtree and cur itself,
                    so go to its right subtree
                    */
                    cur = cur->right;
                }
            }else{
                doWork();
                // cout << cur->val << endl;
                cur = cur->right;
            }
        }
        
        if(first != nullptr && second != nullptr){
            swap(first->val, second->val);
        }
    }
};
