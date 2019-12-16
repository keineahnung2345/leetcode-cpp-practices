//Runtime: 28 ms, faster than 35.18% of C++ online submissions for Recover a Tree From Preorder Traversal.
//Memory Usage: 20 MB, less than 21.05% of C++ online submissions for Recover a Tree From Preorder Traversal.

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
    vector<int> values;
    vector<int> levels;
    
    TreeNode* _recoverFromPreorder(int startIndex, int endIndex, int nodeLevel){
        if(startIndex >= endIndex) return NULL;
        TreeNode* node = new TreeNode(values[startIndex]);
        
        vector<int>::iterator startIt = find(levels.begin()+startIndex+1, levels.begin()+endIndex, nodeLevel+1);
        vector<int>::iterator midIt = find(startIt+1, levels.begin()+endIndex, nodeLevel+1);
        startIndex = startIt - levels.begin();
        int midIndex;
        if(midIt == levels.end()) midIndex = endIndex; //exclusive
        else midIndex = midIt - levels.begin();
        //[startIndex, endIndex) is the range of this subtree
        
        // cout << "start: " << startIndex << ", mid: " << midIndex << ", end: " << endIndex << endl;
        
        //left subtree
        node->left = _recoverFromPreorder(startIndex, midIndex, nodeLevel+1);
        //right subtree
        if(midIndex != endIndex){
            node->right = _recoverFromPreorder(midIndex, endIndex, nodeLevel+1);
        }
        
        return node;
    }
    
    TreeNode* recoverFromPreorder(string S) {
        if(S.size() == 0) return NULL;
        
        int dashIndex = S.find('-');
        TreeNode* root = new TreeNode(stoi(S.substr(0, dashIndex)));
        int numIndex, tmp;
        values.push_back(stoi(S.substr(0, dashIndex)));
        levels.push_back(0);
        
        while(dashIndex != -1){
            numIndex = S.find_first_of("0123456789", dashIndex+1);
            tmp = S.find('-', numIndex+1);
            if(tmp != -1){
                values.push_back(stoi(S.substr(numIndex, tmp-numIndex)));
            }else{
                values.push_back(stoi(S.substr(numIndex)));
            }
            levels.push_back(numIndex - dashIndex);
            dashIndex = tmp;
        }
        
//         for(int e : values){
//             cout << e << " ";
//         }
//         cout << endl;
        
//         for(int e : levels){
//             cout << e << " ";
//         }
//         cout << endl;
        
        vector<int>::iterator startIt = find(levels.begin(), levels.end(), 1);
        vector<int>::iterator endIt = find(startIt+1, levels.end(), 1);
        int startIndex = startIt - levels.begin();
        int endIndex;
        if(endIt == levels.end()) endIndex = levels.size(); //exclusive
        else endIndex = endIt - levels.begin();
        //[startIndex, endIndex) is the range of this subtree
        
        // cout << "start: " << startIndex << ", end: " << endIndex << endl;
        
        //left subtree
        root->left = _recoverFromPreorder(startIndex, endIndex, 1);
        //right subtree
        if(endIndex != levels.size()){
            root->right = _recoverFromPreorder(endIndex, levels.size(), 1);
        }
        
        return root;
    }
};

//[Java/C++/Python] Iterative Stack Solution
//https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/discuss/274621/JavaC%2B%2BPython-Iterative-Stack-Solution
//Runtime: 12 ms, faster than 99.64% of C++ online submissions for Recover a Tree From Preorder Traversal.
//Memory Usage: 11.1 MB, less than 100.00% of C++ online submissions for Recover a Tree From Preorder Traversal.
//Time O(S), Space O(N)

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
    TreeNode* recoverFromPreorder(string S) {
        int level, value;
        TreeNode* node;
        stack<TreeNode*> stk;
        
        //no i++ in this for loop!
        for(int i = 0; i < S.size();){
            level = 0;
            value = 0;
            //&& i < S.size() is important!
            for(; S[i]=='-' && i < S.size(); i++){
                level++;
            }
            for(; S[i]!='-' && i < S.size(); i++){
                value = value * 10 + (S[i] - '0');
            }
            // cout << level << " " << value << endl;
            node = new TreeNode(value);
            //create connection with one of previous nodes
            while(stk.size() > level){
                //when current node is level 1, 
                //we expect that the stack contains only 1 node(at level 0)
                stk.pop();
            }
            // cout << stk.size() << endl;
            if(!stk.empty()){
                //set this node as its parent's left or right child
                if(!stk.top()->left)stk.top()->left = node;
                else stk.top()->right = node;
            }
            //push it into stack
            stk.push(node);
            // cout << stk.size() << endl;
        }
        
        //to get the very first node
        while(!stk.empty()){
            node = stk.top();
            stk.pop();
        }
        
        return node;
    }
};
