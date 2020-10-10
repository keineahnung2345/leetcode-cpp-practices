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
