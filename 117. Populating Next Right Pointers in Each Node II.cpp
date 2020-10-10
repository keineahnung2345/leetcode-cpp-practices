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
