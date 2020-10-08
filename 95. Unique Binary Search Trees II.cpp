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

//recursion + memorization
//note that a tree's range must be continuous, so we can use start and end to identify a tree
//Runtime: 12 ms, faster than 95.32% of C++ online submissions for Unique Binary Search Trees II.
//Memory Usage: 12.3 MB, less than 88.56% of C++ online submissions for Unique Binary Search Trees II.
class Solution {
public:
    vector<vector<vector<TreeNode*>>> memo;
    
    void generateTrees(int start, int end){
        // cout << start << " - " << end << endl;
        
        if(!memo[start][end].empty()){
            return;
        }
        
        if(start > end){
            memo[start][end] = {nullptr};
            return;
        }
        
        vector<TreeNode*> trees;
        for(int v = start; v <= end; ++v){
            generateTrees(start, v-1);
            vector<TreeNode*>& ltree = memo[start][v-1];
            
            generateTrees(v+1, end);
            vector<TreeNode*>&rtree = memo[v+1][end];
        
            // cout << "left: " << ltrees.size() << endl;
            // cout << "right: " << rtrees.size() << endl;
            
            for(int li = 0; li < ltree.size(); ++li){
                for(int ri = 0; ri < rtree.size(); ++ri){
                    TreeNode* root = new TreeNode(v);
                    root->left = ltree[li];
                    root->right = rtree[ri];
                    trees.push_back(root);
                }
            }
        }
        if(trees.empty()) trees.push_back(nullptr);
        memo[start][end] = trees;
    }
    
    vector<TreeNode*> generateTrees(int n) {
        if(n == 0) return {};
        //[1,n] x [1,n] is valid range
        //but 0 and n+1 are also used for convenience
        memo = vector<vector<vector<TreeNode*>>>(n+2, 
            vector<vector<TreeNode*>>(n+2));
        generateTrees(1, n);
        return memo[1][n];
    }
};

//bottom-up DP
//https://leetcode.com/problems/unique-binary-search-trees-ii/discuss/31493/Java-Solution-with-DP
//Runtime: 20 ms, faster than 66.68% of C++ online submissions for Unique Binary Search Trees II.
//Memory Usage: 12.8 MB, less than 83.42% of C++ online submissions for Unique Binary Search Trees II.
class Solution {
public:
    TreeNode* addOffset(TreeNode* node, int offset){
        /*
        clone the whole tree rooted at "node",
        but adding "offset" to all of its descendents
        */
        if(!node) return nullptr;
        TreeNode* newnode = new TreeNode(node->val+offset);
        
        newnode->left = addOffset(node->left, offset);
        newnode->right = addOffset(node->right, offset);
        
        return newnode;
    }
    
    vector<TreeNode*> generateTrees(int n) {
        if(n == 0) return {};
        
        vector<vector<TreeNode*>> dp(n+1);
        
        dp[0] = {nullptr};
        
        //count: size of tree
        for(int count = 1; count <= n; ++count){
            //val: root's value
            for(int val = 1; val <= count; ++val){
                // cout << count << ", " << val << endl;
                for(TreeNode* ltree : dp[val-1]){
                    for(TreeNode* rtree : dp[count-val]){
                        TreeNode* node = new TreeNode(val);
                        node->left = ltree;
                        node->right = addOffset(rtree, val);
                        dp[count].push_back(node);
                    }
                }
            }
        }
        
        return dp[n];
    }
};
