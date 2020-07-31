//only go up or bottom-right, this cannot work
//WA
//47 / 113 test cases passed.
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
    vector<TreeNode*> leaves;
    unordered_map<TreeNode*, TreeNode*> parents;
    int ans;
    
    void buildParents(TreeNode* node, TreeNode* parent){
        parents[node] = parent;
        if(!node->left && !node->right) leaves.push_back(node);
        if(node->left) buildParents(node->left, node);
        if(node->right) buildParents(node->right, node);
    };
    
    void findGoodPairs(TreeNode* node, TreeNode* last, int distance){
        //either go up or go bottom-right
        if(distance < 0) return;
        if(last && !node->left && !node->right) ++ans;
        
        if(parents[node] && parents[node] != last){
            findGoodPairs(parents[node], node, distance-1);
        }
        if(node->right && node->right != last){
            findGoodPairs(node->right, node, distance-1);
        }
    }
    
    int countPairs(TreeNode* root, int distance) {
        buildParents(root, nullptr);
        
        ans = 0;
        
        for(TreeNode* leaf : leaves){
            findGoodPairs(leaf, nullptr, distance);
        }
        
        return ans;
    }
};

//dfs, use visited array
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

//Post order traversal
//https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/discuss/755784/Java-Detailed-Explanation-Post-Order-Cache-in-Array
//Runtime: 128 ms, faster than 57.60% of C++ online submissions for Number of Good Leaf Nodes Pairs.
//Memory Usage: 35.4 MB, less than 68.22% of C++ online submissions for Number of Good Leaf Nodes Pairs.
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
    int ans;
    
    vector<int> helper(TreeNode* node, int distance){
        //i: the distance from node's PARENT to leaves
        //dist2counts[i]: such leaves' count
        //from problem description, 0 <= distance <= 10, so we only need a length 11 array
        vector<int> dist2counts(11, 0);
        
        if(!node) return dist2counts;
        
        if(!node->left && !node->right){
            //first 1 : PARENT to current node's distance
            //second 1: the count is one
            dist2counts[1] = 1;
            return dist2counts;
        }
        
        vector<int> left = helper(node->left, distance);
        vector<int> right = helper(node->right, distance);
        
        for(int i = 0; i < 10; ++i){
            //left[i]: starting from current node, there are left[i] leaves distance i
            //i+1: distance from node to leaf + distance from node's parent to node
            dist2counts[i+1] += left[i]+right[i];
        }
        
        for(int i = 0; i <= 10; ++i){
            for(int j = 0; i+j <= distance; ++j){
                //i and j are distance from current node to leaves
                ans += (left[i]*right[j]);
            }
        }
        
        // cout << "node: " << node->val << endl;
        // for(int i = 0; i < 11; ++i){
        //     cout << left[i] << " ";
        // }
        // cout << endl;
        // for(int i = 0; i < 11; ++i){
        //     cout << right[i] << " ";
        // }
        // cout << endl;
        // for(int i = 0; i < 11; ++i){
        //     cout << dist2counts[i] << " ";
        // }
        // cout << endl;
        return dist2counts;
    };
    
    int countPairs(TreeNode* root, int distance) {
        ans = 0;
        helper(root, distance);
        return ans;
    }
};
