//BFS with queue
//Runtime: 20 ms, faster than 94.93% of C++ online submissions for Populating Next Right Pointers in Each Node.
//Memory Usage: 17.5 MB, less than 16.36% of C++ online submissions for Populating Next Right Pointers in Each Node.
//time: O(N), space: O(N)
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        if(!root) return root;
        
        queue<Node*> q;
        
        q.push(root);
        
        while(!q.empty()){
            int level_size = q.size();
            
            Node* prev = nullptr;
            
            while(level_size-- > 0){
                Node* cur = q.front(); q.pop();
                
                if(prev) prev->next = cur;
                
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
                
                prev = cur;
            }
        }
        
        return root;
    }
};

//O(1) iterative solution
//https://leetcode.com/problems/populating-next-right-pointers-in-each-node/discuss/37472/A-simple-accepted-solution
//Right Pointers in Each Node.
//Memory Usage: 17 MB, less than 16.36% of C++ online submissions for Populating Next Right Pointers in Each Node.
//time: O(N), space: O(1)
class Solution {
public:
    Node* connect(Node* root) {
        if(!root) return root;
        
        Node *prev = root, *cur = nullptr;
        
        //while prev is not a leaf
        while(prev->left){
            //in each iteration, connect all nodes in prev's next level
            cur = prev;
            while(cur){
                cur->left->next = cur->right;
                if(cur->next) cur->right->next = cur->next->left;
                //move rightward, in the same level
                cur = cur->next;
            }
            //go to next level
            prev = prev->left;
        }
        
        return root;
    }
};
