//Runtime: 52 ms, faster than 76.46% of C++ online submissions for Validate Binary Tree Nodes.
//Memory Usage: 12.5 MB, less than 100.00% of C++ online submissions for Validate Binary Tree Nodes.
class Solution {
public:
    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
        vector<int> children;
        
        for(int e : leftChild){
            if(e != -1) children.push_back(e);
        }
        
        for(int e : rightChild){
            if(e != -1) children.push_back(e);
        }
        
        //a valid tree should have exactly n-1 edges
        if(children.size() != n-1) return false;
        
        return true;
    }
};
