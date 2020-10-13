//WA
//this algo points to random node with right value but wrong index
//11 / 19 test cases passed.
//[[3,null],[3,0],[3,null]]
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return nullptr;
        
        Node* dummy = new Node(-1);
        Node* newprev = dummy;
        unordered_map<int, Node*> val2newnodes;
        
        Node* cur = head;
        
        while(cur){
            Node* node = new Node(cur->val);
            val2newnodes[node->val] = node;;
            newprev->next = node;
            newprev = newprev->next;
            cur = cur->next;
        }
        
        Node* newcur = dummy->next;
        
        cur = head;
        newcur = dummy->next;
        while(cur){
            newcur->random = (cur->random) ? val2newnodes[cur->random->val] : nullptr;
            cur = cur->next;
            newcur = newcur->next;
        }
        
        return dummy->next;
    }
};

//using the map old2new
//Runtime: 16 ms, faster than 58.60% of C++ online submissions for Copy List with Random Pointer.
//Memory Usage: 11.5 MB, less than 12.63% of C++ online submissions for Copy List with Random Pointer.
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return nullptr;
        
        Node* dummy = new Node(-1);
        Node* newprev = dummy;
        unordered_map<Node*, Node*> old2new;
        
        Node* cur = head;
        
        while(cur){
            Node* node = new Node(cur->val);
            //temporarily point to random nodes in old list
            //later we will update it
            node->random = cur->random;
            old2new[cur] = node;
            newprev->next = node;
            newprev = newprev->next;
            cur = cur->next;
        }
        
        Node* newcur = dummy->next;
        
        cur = head;
        newcur = dummy->next;
        while(cur){
            newcur->random = (newcur->random) ? old2new[newcur->random] : nullptr;
            cur = cur->next;
            newcur = newcur->next;
        }
        
        return dummy->next;
    }
};

//build interleaving list to save space
//Runtime: 12 ms, faster than 91.43% of C++ online submissions for Copy List with Random Pointer.
//Memory Usage: 11.3 MB, less than 12.63% of C++ online submissions for Copy List with Random Pointer.
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return nullptr;
        
        Node* cur = head;
        
        //bulid the interweaving list
        while(cur){
            Node* node = new Node(cur->val);
            node->next = cur->next;
            cur->next  = node;
            cur = node->next;
        }
        
        //assign "random"
        cur = head;
        Node* newcur;
        
        while(cur){
            newcur = cur->next;
            newcur->random = cur->random ? cur->random->next : nullptr;
            cur = cur->next->next;
        }
        
        //split the interleaving list to two lists
        Node* newhead = head->next;
        newcur = newhead;
        cur = head;
        while(newcur){
            Node* next = cur->next ? cur->next->next : nullptr;
            Node* newnext = newcur->next ? newcur->next->next : nullptr;
            cur->next = cur->next ? cur->next->next : nullptr;
            newcur->next = newcur->next ? newcur->next->next : nullptr;
            newcur = newnext;
            cur = next;
        }
        
        return newhead;
    }
};
