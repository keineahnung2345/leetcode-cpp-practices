//Runtime: 40 ms, faster than 12.32% of C++ online submissions for Lowest Common Ancestor of a Binary Tree.
//Memory Usage: 15.9 MB, less than 100.00% of C++ online submissions for Lowest Common Ancestor of a Binary Tree.
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int pLevel = -1, qLevel = -1;
        
        queue<TreeNode*> bfsq;
        TreeNode* cur;
        int levelCount = 0;
        int level = 0;
        map<TreeNode*, TreeNode*> parents;
        
        bfsq.push(root);
        parents[root] = nullptr;
        levelCount++;
        
        while(!bfsq.empty()){
            // cout << level << " " << levelCount << endl;
            while(levelCount-- > 0){
                cur = bfsq.front(); bfsq.pop();
                if(cur == p){
                    pLevel = level;
                }
                if(cur == q){
                    qLevel = level;
                }
                if(cur->left){
                    bfsq.push(cur->left);
                    parents[cur->left] = cur;
                }
                if(cur->right){
                    bfsq.push(cur->right);
                    parents[cur->right] = cur;
                }
            }
            level++;
            levelCount = bfsq.size();
        }
        
        //lift the lower one to the same level
        while(qLevel > pLevel){
            qLevel--;
            q = parents[q];
        }
        
        while(pLevel > qLevel){
            pLevel--;
            p = parents[p];
        }
        
        //now p and q are at same level
        if(p == q) return p;
        
        while(p != q){
            p = parents[p];
            q = parents[q];
        }
        
        // cout << pLevel << " " << qLevel << endl;
        
        return p;
    }
};

//Approach 1: Recursive Approach
//Runtime: 20 ms, faster than 79.55% of C++ online submissions for Lowest Common Ancestor of a Binary Tree.
//Memory Usage: 14.3 MB, less than 100.00% of C++ online submissions for Lowest Common Ancestor of a Binary Tree.
//time: O(N), space: O(N)
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
    TreeNode *p, *q, *ans;
    
    bool recurseTree(TreeNode* cur){
        if(cur == nullptr) return false;
        
        int mid = (int)(cur == p || cur == q);
        int left = (int)recurseTree(cur->left);
        int right = (int)recurseTree(cur->right);
        
        /*
        mid & left : current node is lca
        mid & right: current node is lca
        left& right: their parent, which is current node, is lca
        */
        if(mid + left + right >= 2){
            ans = cur;
        }
        
        //if itself or one of its children is p or q's ancestor
        return mid + left + right > 0;
    };
    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        this->p = p;
        this->q = q;
        recurseTree(root);
        return ans;
    }
};
