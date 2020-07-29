//Runtime: 680 ms, faster than 7.28% of C++ online submissions for Number of Good Leaf Nodes Pairs.
//Memory Usage: 92.3 MB, less than 6.17% of C++ online submissions for Number of Good Leaf Nodes Pairs.
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
    set<TreeNode*> visited;
    vector<TreeNode*> leaves;
    unordered_map<TreeNode*, TreeNode*> parents;
    int ans;
    
    void buildParentsAndLeaves(TreeNode* node, TreeNode* parent){
        parents[node] = parent;
        if(!node->left && !node->right) leaves.push_back(node);
        if(node->left) buildParentsAndLeaves(node->left, node);
        if(node->right) buildParentsAndLeaves(node->right, node);
    };
    
    void findGoodPairs(TreeNode* node, TreeNode* last, int distance){
        if(distance < 0) return;
        //if(last): it's not source
        if(last && !node->left && !node->right) ++ans;
        
        if(parents[node] && visited.find(parents[node]) == visited.end()){
            visited.insert(parents[node]);
            findGoodPairs(parents[node], node, distance-1);
        }
        if(node->right && visited.find(node->right) == visited.end()){
            visited.insert(node->right);
            findGoodPairs(node->right, node, distance-1);
        }
        //need to go left!
        if(node->left && visited.find(node->left) == visited.end()){
            visited.insert(node->left);
            findGoodPairs(node->left, node, distance-1);
        }
    }
    
    int countPairs(TreeNode* root, int distance) {
        buildParentsAndLeaves(root, nullptr);
        
        ans = 0;
        
        // cout << "leaves: ";
        // for(TreeNode* leaf : leaves){
        //     cout << leaf->val << " ";
        // }
        // cout << endl;
        
        for(TreeNode* leaf : leaves){
            visited.insert(leaf);
            findGoodPairs(leaf, nullptr, distance);
            visited.clear();
        }
        
        return ans>>1;
    }
};
