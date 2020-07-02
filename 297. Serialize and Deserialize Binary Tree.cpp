//Runtime: 452 ms, faster than 5.05% of C++ online submissions for Serialize and Deserialize Binary Tree.
//Memory Usage: 38.7 MB, less than 41.53% of C++ online submissions for Serialize and Deserialize Binary Tree.
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
    template <typename Iter>
    std::string join(Iter begin, Iter end, std::string const& separator)
    {
        std::ostringstream result;
        result.precision(2); //for floating point
        if (begin != end)
            result << *begin++;
        while (begin != end)
            //std::fixed : for floating point
            result << std::fixed << separator << *begin++;
        return result.str();
    }
    
    std::vector<std::string> string_split(std::string str, std::string delimiter){
        size_t pos = 0;
        std::string token;
        std::vector<std::string> result;

        //Style 2, can deal with all tokens inside the while loop
        while(true){
            pos = str.find(delimiter);
            //works even if pos is string::npos
            token = str.substr(0, pos);
            result.push_back(token);
            if(pos == string::npos) break;
            //pos+1 equals to 0, so the line below can't handle this situation
            str.erase(0, pos+delimiter.length());
        }
        return result;
    }
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        vector<string> tokens;
        
        TreeNode* cur;
        queue<TreeNode*> q;
        q.push(root);
        
        while(!q.empty()){
            cur = q.front(); q.pop();
            
            if(cur != nullptr){
                tokens.push_back(to_string(cur->val));
                //we also visit children who are nullptr
                q.push(cur->left);
                q.push(cur->right);
            }else{
                tokens.push_back("null");
            }
        }
        
        return join(tokens.begin(), tokens.end(), ",");
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> tokens = string_split(data, ",");
        int n = tokens.size();
        vector<TreeNode*> nodes(n);
        
        for(int i = 0; i < n; ++i){
            if(tokens[i] == "null"){
                nodes[i] = nullptr;
            }else{
                nodes[i] = new TreeNode(stoi(tokens[i]));
            }
        }
        
        //use bfs to reconstruct tree
        TreeNode* cur;
        int nodeCursor = 0;
        queue<TreeNode*> q;
        q.push(nodes[nodeCursor]);
        
        while(!q.empty()){
            int levelSize = q.size();
            
            //visit level by level
            while(levelSize-- > 0){
                cur = q.front(); q.pop();
                
                if(cur != nullptr){
                    cur->left = nodes[++nodeCursor];
                    cur->right = nodes[++nodeCursor];
                    
                    q.push(cur->left);
                    q.push(cur->right);
                }
            }
        }
        
        return nodes[0];
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

//recursion
//https://leetcode.com/problems/serialize-and-deserialize-binary-tree/discuss/74253/Easy-to-understand-Java-Solution
//Runtime: 624 ms, faster than 5.05% of C++ online submissions for Serialize and Deserialize Binary Tree.
//Memory Usage: 38.2 MB, less than 42.14% of C++ online submissions for Serialize and Deserialize Binary Tree.
class Codec {
public:
    void serial(TreeNode* node, string& str){
        if(node == nullptr){
            str += "null";
        }else{
            str += to_string(node->val) + ",";
            serial(node->left, str); str += ",";
            serial(node->right, str);
        }
    }
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string str = "";
        serial(root, str);
        // cout << "str: " << str << endl;
        return str;
    }

    std::vector<std::string> string_split(std::string str, std::string delimiter){
        size_t pos = 0;
        std::string token;
        std::vector<std::string> result;

        //Style 2, can deal with all tokens inside the while loop
        while(true){
            pos = str.find(delimiter);
            //works even if pos is string::npos
            token = str.substr(0, pos);
            result.push_back(token);
            if(pos == string::npos) break;
            //pos+1 equals to 0, so the line below can't handle this situation
            str.erase(0, pos+delimiter.length());
        }
        return result;
    }
    
    TreeNode* deserial(queue<string>& q){
        string token = q.front(); q.pop();
        if(token == "null") return nullptr;
        TreeNode* root = new TreeNode(stoi(token));
        root->left = deserial(q);
        root->right = deserial(q);
        return root;
    };
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> tokens = string_split(data, ",");
        queue<string, deque<string>> q(deque<string>(tokens.begin(), tokens.end()));
        return deserial(q);
    }
};
