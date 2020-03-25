//Approach 1: Annotate Parent
//Runtime: 12 ms, faster than 32.60% of C++ online submissions for All Nodes Distance K in Binary Tree.
//Memory Usage: 12.9 MB, less than 100.00% of C++ online submissions for All Nodes Distance K in Binary Tree.
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

//Approach 2: Percolate Distance
//Runtime: 4 ms, faster than 93.76% of C++ online submissions for All Nodes Distance K in Binary Tree.
//Memory Usage: 12.4 MB, less than 100.00% of C++ online submissions for All Nodes Distance K in Binary Tree.
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
    vector<int> ans;
    TreeNode* target;
    int K;
    
    /*
    find in the subtree rooted at node,
    if the distance of the root and a node is K,
    then add it into ans
    */
    void subtreeAdd(TreeNode* node, int dist){
        if(node == nullptr) return;
        // cout << node->val << ", dist: " << dist << endl;
        if(dist == K){
            ans.push_back(node->val);
        }else{
            subtreeAdd(node->left, dist+1);
            subtreeAdd(node->right, dist+1);
        }
    };
    
    //if node and connect to target, return their vertex distance
    //else return -1
    //vertex distance: #vertices on path from node to target
    int dfs(TreeNode* node){
        if(!node) return -1;
        if(node == target){
            subtreeAdd(node, 0);
            return 1;
        }
        
        int L = dfs(node->left);
        int R = dfs(node->right);
        if(L != -1){
            //we can find target in left subtree
            if(L == K) ans.push_back(node->val);
            //-1: vertex distance->normal distance
            //+2: node->left to node to node->right
            subtreeAdd(node->right, L-1+2);
            return L-1+2;
        }else if(R != -1){
            if(R == K) ans.push_back(node->val);
            subtreeAdd(node->left, R-1+2);
            return R-1+2;
        }
        //cannot find target in both its left subtree nor right subtree
        return -1;
    };
    
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        this->target = target;
        this->K = K;
        dfs(root);
        return ans;
    }
};
