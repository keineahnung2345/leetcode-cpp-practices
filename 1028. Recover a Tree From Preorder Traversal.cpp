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
