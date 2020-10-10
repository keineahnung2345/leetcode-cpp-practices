//BFS with queue
//Runtime: 20 ms, faster than 52.71% of C++ online submissions for Populating Next Right Pointers in Each Node II.
//Memory Usage: 17.9 MB, less than 66.31% of C++ online submissions for Populating Next Right Pointers in Each Node II.
//time: O(N), space: O(N)
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

//O(1) space iterative solution
//https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/discuss/37811/Simple-solution-using-constant-space
//Runtime: 12 ms, faster than 96.85% of C++ online submissions for Populating Next Right Pointers in Each Node II.
//Memory Usage: 17.7 MB, less than 66.31% of C++ online submissions for Populating Next Right Pointers in Each Node II.
//time: O(N), space: O(1)
class Solution {
public:
    Node* connect(Node* root) {
        //first node of next level
        Node *nhead = nullptr;
        
        Node *prev = nullptr, *cur = root;
        
        while(cur){
            //process cur's next level
            while(cur){
                if(cur->left){
                    if(prev){
                        prev->next = cur->left;
                    }else{
                        nhead = cur->left;
                    }
                    prev = cur->left;
                }
                //else 
                if(cur->right){
                    if(prev){
                        prev->next = cur->right;
                    }else{
                        nhead = cur->right;
                    }
                    prev = cur->right;
                }
                //go to next node in current level
                cur = cur->next;
            }
            
            //go to next level
            cur = nhead;
            prev = nhead = nullptr;
        }
        
        return root;
    }
};

//O(1) space(not consider recursion stack) recursive solution
//https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/discuss/172861/Mostly-recursive-solution-O(n)-time-(beats-99.32)-and-O(1)-space-(without-considering-stack)
//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Populating Next Right Pointers in Each Node II.
//Memory Usage: 17.6 MB, less than 66.31% of C++ online submissions for Populating Next Right Pointers in Each Node II.
class Solution {
public:
    Node* findnext(Node* node){
        //recursively find the next leftmost child
        if(!node) return node;
        if(node->left) return node->left;
        if(node->right) return node->right;
        //current node is leaf, go to its right neighbor
        return findnext(node->next);
    }
    
    Node* connect(Node* root) {
        if(!root) return root;
        
        if(root->left){
            Node* target;
            if(root->right){
                target = root->right;
            }else{
                target = findnext(root->next);
            }
            root->left->next = target;
        }
        
        if(root->right){
            root->right->next = findnext(root->next);
        }
        
        //https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/discuss/172861/Mostly-recursive-solution-O(n)-time-(beats-99.32)-and-O(1)-space-(without-considering-stack)/260137
        /*
        in the function "findnext",
        we will recursively go right,
        and it requires that the right subtree is connected first,
        otherwise, therewill be a gap btw left and right subtree
        
        consider: [2,1,3,0,7,9,1,2,null,1,0,null,null,8,8,null,null,null,null,7]
        */
        connect(root->right);
        connect(root->left);
        
        return root;
    }
};
