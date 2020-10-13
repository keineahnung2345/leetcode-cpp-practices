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
