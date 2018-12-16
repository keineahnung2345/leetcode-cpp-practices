/**
Given a n-ary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

For example, given a 3-ary tree:

We should return its max depth, which is 3.

Note:

The depth of the tree is at most 1000.
The total number of nodes is at most 5000.
**/

//Your runtime beats 11.70 % of cpp submissions.
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
    int maxDepth(Node* root) {
        if(root==NULL) return 0;
        
        int childDepth = 0;
        for(Node* child : root->children){
            childDepth = max(childDepth, maxDepth(child));
        }
        return 1+childDepth;
    }
};

/**
Solution
Tree definition

First of all, please refer to this article for the solution in case of binary tree. 
https://leetcode.com/articles/maximum-depth-of-binary-tree/ offers the same ideas with a bit of generalisation.
**/

/**
Approach 1: Recursion
Algorithm

The intuitive approach is to solve the problem by recursion. 
Here we demonstrate an example with the DFS (Depth First Search) strategy.
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

//Your runtime beats 67.95 % of cpp submissions.
class Solution {
public:
    int maxDepth(Node* root) {
        if(root==NULL){
            return 0;
        }else if(root->children.empty()){
            return 1;
        }else{
            int childDepth = 0;
            for(Node* child : root->children){
                childDepth = max(childDepth, maxDepth(child));
            }
            return 1+childDepth;
        }
    }
};
/**
Complexity analysis

Time complexity : we visit each node exactly once, thus the time complexity is O(N), where N is the number of nodes.

Space complexity : in the worst case, the tree is completely unbalanced, 
e.g. each node has only one child node, the recursion call would occur N times (the height of the tree),
therefore the storage to keep the call stack would be O(N). 
But in the best case (the tree is completely balanced), the height of the tree would be log(N). 
Therefore, the space complexity in this case would be O(log(N)). 
**/

/**
Approach 2: Iteration
We could also convert the above recursion into iteration, with the help of stack.

The idea is to visit each node with the DFS strategy, while updating the max depth at each visit.

So we start from a stack which contains the root node and the corresponding depth which is 1. 
Then we proceed to the iterations: pop the current node out of the stack and push the child nodes. 
The depth is updated at each step.
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

//Your runtime beats 29.52 % of cpp submissions.
class Solution {
public:
    int maxDepth(Node* root) {
        stack<pair<Node*, int> > stk;
        int depth = 0;
        
        if(root!=NULL)
            stk.push(make_pair(root, 1));
        
        while(!stk.empty()){
            pair<Node*, int> p = stk.top();
            stk.pop();
            
            Node* node = p.first;
            int currentDepth = p.second;
            depth = max(depth, currentDepth);
            
            for(Node* child : node->children){
                stk.push(make_pair(child, currentDepth+1));
            }
            
        }
        
        return depth;
    }
};

/**
Complexity analysis

Time complexity : O(N).

Space complexity : O(N).
**/
