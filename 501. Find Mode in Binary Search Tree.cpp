/**Using map**/

//Runtime: 36 ms, faster than 51.88% of C++ online submissions for Find Mode in Binary Search Tree.
//Memory Usage: 24.9 MB, less than 49.51% of C++ online submissions for Find Mode in Binary Search Tree.

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
    vector<int> findMode(TreeNode* root) {
        if(root == NULL) return vector<int>();
        map<int, int> count;
        queue<TreeNode*> q;
        TreeNode* cur;
        int maxcount = 0;
        vector<int> ans;
        
        q.push(root);
        
        while(!q.empty()){
            cur = q.front();
            q.pop();
            
            if(count.find(cur->val) == count.end()){
                count[cur->val] = 1;
            }else{
                count[cur->val]++;
            }
            maxcount = max(maxcount, count[cur->val]);
            
            if(cur->left) q.push(cur->left);
            if(cur->right) q.push(cur->right);
            
        }
        
        for(map<int,int>::iterator it = count.begin(); it!=count.end(); it++){
            if(it->second == maxcount) ans.push_back(it->first);
        }
        
        return ans;
    }
};

/**Without map**/
//https://leetcode.com/problems/find-mode-in-binary-search-tree/discuss/98100/Java-4ms-Beats-100-Extra-O(1)-solution-No-Map

class Solution {
public:
    vector<int> ans;
    int prev = INT_MIN;
    int curcount = 1; //since we only update curcount when it's not first node
    int maxcount = 0;
    
    void traverse(TreeNode* root){
        if(!root) return;
        traverse(root->left);
        //we only update curcount when it's not first node
        if(prev != INT_MIN){
            if(root->val == prev){
                curcount++;
            }else{
                curcount = 1;
            }
        }
        prev = root->val;
        if(curcount > maxcount){
            maxcount = curcount;
            ans.clear();
            // cout << "if: " << curcount << " " << maxcount << " " << root->val << endl;
            ans.push_back(root->val);
        }else if(curcount == maxcount){
            // cout << "else: " << curcount << " " << maxcount << " " << root->val << endl;
            ans.push_back(root->val);
        }
        traverse(root->right);
    }
    
    vector<int> findMode(TreeNode* root) {
        if(!root) return vector<int>();
        traverse(root);
        cout << endl;
        return ans;
    }
};
