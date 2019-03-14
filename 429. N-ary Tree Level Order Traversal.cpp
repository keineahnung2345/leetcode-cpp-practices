/**
Given an n-ary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).
**/

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

//Runtime: 160 ms, faster than 93.75% of C++ online submissions for N-ary Tree Level Order Traversal.
//Memory Usage: 34.3 MB, less than 6.06% of C++ online submissions for N-ary Tree Level Order Traversal.
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        if(root==NULL){
            return vector<vector<int>>();
        }
        
        queue<Node*> q;
        //root: level 0, 1 node in this level
        int level = 0, levelCount = 1, nextLevelCount = 0;
        vector<vector<int>> ans;
        vector<int> levelAns;
        
        q.push(root);
        
        while(!q.empty()){
            Node* cur = q.front();
            q.pop();
            for(Node* c : cur->children){
                if(c!=NULL)q.push(c);
            }
            
            nextLevelCount+=cur->children.size();
            levelAns.push_back(cur->val);
            
            levelCount--;
            if(levelCount==0){
                //We have seen all nodes in this level
                ans.push_back(levelAns);
                //need a new vector
                levelAns = vector<int>();
                //levelCount
                levelCount = nextLevelCount;
                nextLevelCount = 0;
                level++;
            }
        }
        
        return ans;
    }
};
