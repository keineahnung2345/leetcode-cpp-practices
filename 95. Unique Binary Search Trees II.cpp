//recursion
//Runtime: 36 ms, faster than 10.54% of C++ online submissions for Unique Binary Search Trees II.
//Memory Usage: 18.2 MB, less than 5.04% of C++ online submissions for Unique Binary Search Trees II.
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
    int n;
    
    void generateTrees(vector<bool>& used, vector<TreeNode*>& trees){
        for(int v = 1; v <= n; ++v){
            if(used[v]) continue;
            used[v] = true;
            
            vector<bool> lused = used;
            vector<TreeNode*> ltrees;
            //elements larger than v is not usable
            for(int lv = v+1; lv <= n; ++lv){
                lused[lv] = true;
            }
            generateTrees(lused, ltrees);
            
            vector<bool> rused = used;
            vector<TreeNode*> rtrees;
            for(int rv = 1; rv < v; ++rv){
                rused[rv] = true;
            }
            generateTrees(rused, rtrees);
            
            // cout << "left: " << ltrees.size() << endl;
            // cout << "right: " << rtrees.size() << endl;
            
            for(int li = 0; li < ltrees.size(); ++li){
                for(int ri = 0; ri < rtrees.size(); ++ri){
                    TreeNode* root = new TreeNode(v);
                    root->left = ltrees[li];
                    root->right = rtrees[ri];
                    trees.push_back(root);
                }
            }
            
            used[v] = false;
        }
        if(trees.empty()) trees.push_back(nullptr);
    }
    
    vector<TreeNode*> generateTrees(int n) {
        if(n == 0) return {};
        
        this->n = n;
        //0 is for padding
        vector<bool> used(n+1, false);
        vector<TreeNode*> trees;
        
        generateTrees(used, trees);
        
        return trees;
    }
};
