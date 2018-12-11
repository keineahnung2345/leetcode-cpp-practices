/**
Given an n-ary tree, return the postorder traversal of its nodes' values.

For example, given a 3-ary tree:

Return its postorder traversal as: [5,6,3,2,4,1].

Note:

Recursive solution is trivial, could you do it iteratively?
**/

//recursive
//Your runtime beats 40.15 % of cpp submissions.
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
class Solution {
public:
    vector<int> ans;
    void _postorder(Node* node){
        if(node==NULL) return;
        
        for(Node* child : node->children){
            _postorder(child);
        }
        
        ans.push_back(node->val);
    }
    vector<int> postorder(Node* root) {
        _postorder(root);
        return ans;
    }
};

//iterative
//Your runtime beats 82.71 % of cpp submissions.
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
class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int> ans;
        stack<Node*> stk;
        
        stk.push(root);
        
        while(!stk.empty()){
            Node* node = stk.top();
            stk.pop();
            
            if(node==NULL)continue;
            
            for(Node* child : node->children){
                stk.push(child);
            }
            
            ans.insert(ans.begin(), node->val);
        }
        return ans;
    }
};

/**
Approach 1: Iterations
Algorithm

First of all, here is the definition of the TreeNode which we would use in the following implementation.

Let's start from the root and then at each iteration pop the current node out of the stack and push its child nodes. 
In the implemented strategy we push nodes into stack following the order Top->Bottom and Left->Right. 
Since DFS postorder traversal is Bottom->Top and Left->Right the output list should be reverted after the end of loop.

Complexity Analysis

Time complexity : we visit each node exactly once, 
thus the time complexity is O(N), where N is the number of nodes, i.e. the size of tree.

Space complexity : depending on the tree structure, we could keep up to the entire tree, 
therefore, the space complexity is O(N).
**/
