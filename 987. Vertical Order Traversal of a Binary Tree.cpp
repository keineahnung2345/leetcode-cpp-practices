//map, multiset(both are sorted)
//Runtime: 4 ms, faster than 93.71% of C++ online submissions for Vertical Order Traversal of a Binary Tree.
//Memory Usage: 14.9 MB, less than 11.43% of C++ online submissions for Vertical Order Traversal of a Binary Tree.
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
    //(x, y) -> values
    map<int, map<int, multiset<int>>> coord2values;
    
    void dfs(TreeNode* node, int x, int y){
        if(node == nullptr) return;
        
        coord2values[x][y].insert(node->val);
        
        /*
        from problem description,
        we should use y-1 here,
        but because we want it sort y in descending order,
        we don't bother to change our data structure,
        but here we change the definition of y
        */
        dfs(node->left, x-1, y+1);
        dfs(node->right, x+1, y+1);
    }
    
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        dfs(root, 0, 0);
        
        vector<vector<int>> ans;
        
        for(auto itx = coord2values.begin(); itx != coord2values.end(); ++itx){
            vector<int> line;
            for(auto ity = itx->second.begin(); ity != itx->second.end(); ++ity){
                // cout << "(" << itx->first << ", " << ity->first << "): ";
                // for(auto itn = ity->second.begin(); itn != ity->second.end(); ++itn){
                //     cout << *itn << " ";
                // }
                // cout << endl;
                line.insert(line.end(), ity->second.begin(), ity->second.end());
            }
            ans.push_back(line);
        }
        
        return ans;
    }
};
