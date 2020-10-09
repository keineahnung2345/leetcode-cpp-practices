//use upper and lower boundaries to check whether we should add null
//https://leetcode.com/problems/serialize-and-deserialize-bst/discuss/177617/the-General-Solution-for-Serialize-and-Deserialize-BST-and-Serialize-and-Deserialize-BT
//Runtime: 40 ms, faster than 84.94% of C++ online submissions for Serialize and Deserialize BST.
//Memory Usage: 28.7 MB, less than 5.45% of C++ online submissions for Serialize and Deserialize BST.
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    void serialize(TreeNode* node, string& s){
        if(!node) return;
        
        //preorder
        s += to_string(node->val) + " ";
        serialize(node->left, s);
        serialize(node->right, s);
    }
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s;
        serialize(root, s);
        // cout << s << endl;
        return s;
    }
    
    TreeNode* deserialize(queue<string>& q, int lower, int upper){
        if(q.empty()) return nullptr;
        
        int val = stoi(q.front());
        // cout << "checking " << val << endl;
        if(val < lower || val > upper) return nullptr;
        
        //only pop the string after ensuring it can be used here
        q.pop();
        
        // cout << val << " is used" << endl;
        
        TreeNode* node = new TreeNode(val);
        // cout << val << "'s left" << endl;
        node->left = deserialize(q, lower, val);
        // cout << val << "'s right" << endl;
        node->right = deserialize(q, val, upper);
        return node;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data.empty()) return nullptr;
        
        istringstream ss(data);
        queue<string> q;
        string s;
        
        while(ss >> s){
            q.push(s);
        }
        
        return deserialize(q, INT_MIN, INT_MAX);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;
