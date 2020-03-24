//Runtime: 4 ms, faster than 86.00% of C++ online submissions for Smallest Subtree with all the Deepest Nodes.
//Memory Usage: 13.7 MB, less than 100.00% of C++ online submissions for Smallest Subtree with all the Deepest Nodes.
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
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        unordered_map<TreeNode*, TreeNode*> parent;
        TreeNode* cur;
        queue<TreeNode*> q;
        vector<TreeNode*> levelNodes, nextLevelNodes;
        int levelCount = 0, nextLevelCount = 0;
        
        q.push(root);
        parent[root] = nullptr;
        levelCount = 1;
        levelNodes.push_back(root);
        
        while(!q.empty()){
            cur = q.front(); q.pop();
            
            if(cur->left){
                q.push(cur->left);
                nextLevelCount++;
                nextLevelNodes.push_back(cur->left);
                parent[cur->left] = cur;
            }
            
            if(cur->right){
                q.push(cur->right);
                nextLevelCount++;
                nextLevelNodes.push_back(cur->right);
                parent[cur->right] = cur;
            }
            
            levelCount--;
            //update level info if we are not at deepest level
            //(we still have children)
            if(levelCount == 0 && nextLevelCount > 0){
                levelCount = nextLevelCount;
                nextLevelCount = 0;
                levelNodes = nextLevelNodes;
                nextLevelNodes.clear();
                // cout << "levelCount: " << levelCount << endl;
            }
            
        }
        
        // cout << levelNodes.size() << endl;
        // for(int i = 0; i < levelNodes.size(); i++){
        //     cout << levelNodes[i]->val << " ";
        // }
        // cout << endl;
        
        //now levelNodes contains the deepest nodes
        while(true){
            cur = levelNodes[0];
            bool allSame = true;
            for(int i = 1; i < levelNodes.size(); i++){
                if(cur != levelNodes[i]){
                    allSame = false;
                    break;
                }
            }
            if(allSame){
                return cur;
            }
            //move all nodes one level up
            for(int i = 0; i < levelNodes.size(); i++){
                levelNodes[i] = parent[levelNodes[i]];
            }
        }
        
        return nullptr;
    }
};

//DFS, recursion
//Runtime: 4 ms, faster than 86.00% of C++ online submissions for Smallest Subtree with all the Deepest Nodes.
//Memory Usage: 15.7 MB, less than 7.14% of C++ online submissions for Smallest Subtree with all the Deepest Nodes.
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
    unordered_map<TreeNode*, int> depth;
    int maxDepth;
    
    void dfs(TreeNode* node, TreeNode* parent){
        if(node == nullptr) return;
        depth[node] = depth[parent] + 1;
        maxDepth = max(maxDepth, depth[node]);
        dfs(node->left, node);
        dfs(node->right, node);
    };
    
    TreeNode* answer(TreeNode* node){
        //the return value nullptr will be ignored by its caller
        if(node == nullptr) return node;
        if(depth[node] == maxDepth) return node;
        TreeNode *L = answer(node->left);
        TreeNode *R = answer(node->right);
        if(L && R) return node;
        if(L) return L;
        if(R) return R;
        return nullptr;
    };
    
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        maxDepth = -1;
        /*root's parent is nullptr, 
        we want root's depth be 0, so nullptr's depth should be -1
        */
        depth[nullptr] = -1;
        dfs(root, nullptr);
        
        return answer(root);
    }
};
