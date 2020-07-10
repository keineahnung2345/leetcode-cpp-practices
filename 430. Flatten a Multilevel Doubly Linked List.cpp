//Runtime: 4 ms, faster than 97.09% of C++ online submissions for Flatten a Multilevel Doubly Linked List.
//Memory Usage: 7.5 MB, less than 36.59% of C++ online submissions for Flatten a Multilevel Doubly Linked List.
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* flatten(Node* head) {
        if(head == nullptr) return nullptr;
        
        Node* cur;
        stack<Node*> stk;
        
        stk.push(head);
        
        Node* newhead = head;
        
        while(!stk.empty()){
            //cur 
            cur = stk.top(); stk.pop();
            
            //go to the end of list or the node having child
            while(cur->next != nullptr && cur->child == nullptr){
                cur = cur->next;
            }
            
            if(cur->next == nullptr && cur->child != nullptr){
                //end node and has child
                cur->next = cur->child;
                cur->child->prev = cur;
                cur->child = nullptr;
                //need to further visit cur->next
                stk.push(cur->next);
            }else if(cur->next == nullptr){
                //go to the end of current level
                if(!stk.empty()){
                    //stk.top() is the node to be concatenated
                    cur->next = stk.top();
                    stk.top()->prev = cur;
                }
            }else{
                //go to the node having child
                
                //we will later visit its child and then its next
                stk.push(cur->next);
                stk.push(cur->child);
                
                //rewind
                cur->next = cur->child;
                cur->child->prev = cur;
                cur->child = nullptr;
            }
        }
        
        return newhead;
    }
};
