//Runtime: 12 ms, faster than 32.60% of C++ online submissions for All Nodes Distance K in Binary Tree.
//Memory Usage: 12.9 MB, less than 100.00% of C++ online submissions for All Nodes Distance K in Binary Tree.
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
    vector<int> ans;
    map<TreeNode*, TreeNode*> parent;
    
    // void dfs(TreeNode* node, int K){
    //     if(!node) return;
    //     if(K == 0){
    //         ans.push_back(node->val);
    //         return;
    //     }
    //     if(node->left){
    //         dfs(node->left, K-1);
    //     }
    //     if(node->right){
    //         dfs(node->right, K-1);
    //     }
    // };
    
    void dfsUpDown(TreeNode* node, TreeNode* target, int K){
        if(!node) return;
        if(K == 0){
            ans.push_back(node->val);
            return;
        }
        if(parent[node] && parent[node] != target){
            /*
            next time when parent[node] considers which path to take, 
            it will not go to "node" again
            */
            dfsUpDown(parent[node], node, K-1);
        }
        if(node->left && node->left != target){
            /*
            next time when node->left considers which path to take, 
            it will not go to "node" again
            */
            dfsUpDown(node->left, node, K-1);
        }
        if(node->right && node->right != target){
            dfsUpDown(node->right, node, K-1);
        }
    };
    
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        queue<TreeNode*> q;
        TreeNode* cur;
        
        q.push(root);
        parent[root] = nullptr;
        
        while(!q.empty()){
            cur = q.front(); q.pop();
            // if(cur == target) break;
            
            if(cur->left){
                parent[cur->left] = cur;
                q.push(cur->left);
            }
            
            if(cur->right){
                parent[cur->right] = cur;
                q.push(cur->right);
            }
        }
        
        //put its descendent into ans
        dfsUpDown(target, target, K);
        
        return ans;
    }
};
