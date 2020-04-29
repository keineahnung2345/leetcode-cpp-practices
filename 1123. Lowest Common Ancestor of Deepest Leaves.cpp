//Runtime: 16 ms, faster than 80.00% of C++ online submissions for Lowest Common Ancestor of Deepest Leaves.
//Memory Usage: 21.6 MB, less than 100.00% of C++ online submissions for Lowest Common Ancestor of Deepest Leaves.

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
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        //find deepest leaves, and then return their LCA
        map<TreeNode*, TreeNode*> parent; //depth and parent
        int level, level_count, next_level_count;
        vector<TreeNode*> level_nodes;
        queue<TreeNode*> q;
        TreeNode* cur;
        
        //find deepest leaves
        q.push(root);
        level = 0; level_count = 1; next_level_count = 0;
        
        while(!q.empty()){
            cur = q.front(); q.pop();
            level_nodes.push_back(cur);
            
            if(cur->left){
                q.push(cur->left);
                parent[cur->left] = cur;
                next_level_count++;
            }
            
            if(cur->right){
                q.push(cur->right);
                parent[cur->right] = cur;
                next_level_count++;
            }
            
            level_count--;
            if(level_count == 0){
                level_count = next_level_count;
                next_level_count = 0;
                if(!q.empty()){
                    level++;
                    level_nodes.clear();
                }
            }
        }
        //level_nodes is now deepest leaves
        
        //find LCA
        //only one leaf
        // cout << level_nodes.size() << endl;
        if(level_nodes.size() == 1) return level_nodes[0];
        
        //more than one leaf
        TreeNode* first_parent;
        
        while(true){
            first_parent = parent[level_nodes[0]];
            bool same_parent = true;
            for(int i = 1; i < level_nodes.size(); i++){
                if(parent[level_nodes[i]] != first_parent){
                    same_parent = false;
                    break;
                }
            }
            if(same_parent) break;
            //if parent not common, use grandparent
            //this is valid because all "level_nodes" are at the same level!
            for(int i = 0; i < level_nodes.size(); i++){
                parent[level_nodes[i]] = parent[parent[level_nodes[i]]];
            }
        }
        
        return first_parent;   
    }
};
