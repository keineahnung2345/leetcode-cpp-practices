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
