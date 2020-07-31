//Runtime: 20 ms, faster than 39.60% of C++ online submissions for Reverse Nodes in k-Group.
//Memory Usage: 10.3 MB, less than 16.67% of C++ online submissions for Reverse Nodes in k-Group.
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    void reverseTwoNodes(ListNode** a, ListNode** b){
        //a and b are pointer of pointer
        //a->x->... and b->y->... to b->a->x->... and y->...
        // cout << "reverse: " << (*a)->val << " and " << (*b)->val << endl;
        ListNode* latter = (*b)->next;
        (*b)->next = *a;
        //a->(b) and b->y->... to b->a->y->...
        if((*a)->next == *b) (*a)->next = nullptr;
        *a = *b;
        *b = latter;
        // cout << "reversed: " << ((*a) ? (*a)->val : -1) << " and " << ((*b) ? (*b)->val : -1) << endl;
    };
    
    ListNode* reverseKGroup(ListNode* head, int k) {
        //check if the length of list >= k
        ListNode* tail = head;
        //go forward for k-1 steps
        for(int i = 0; i < k-1 && tail; ++i){
            tail = tail->next;
        }
        //the list's length < k, don't need to reverse it
        if(!tail) return head;
        
        //reverse the first k node and call function for rest nodes
        ListNode* laterHead = reverseKGroup(tail->next, k);
        
        // cout << "head: " << head->val << ", tail: " << tail->val << endl;
        ListNode *cur = head, *next = head->next;
        //each time reverse two nodes, reverse for k-1 times
        for(int i = 0; i < k-1; ++i){
            reverseTwoNodes(&cur, &next);
        }
        
        // cout << "new head: " << tail->val << ", new tail: " << head->val << endl;
        // cout << "the reversed group: ";
        // cur = tail;
        // while(cur){
        //     cout << cur->val << " ";
        //     cur = cur->next;
        // }
        // cout << endl;
        
        //original head of group now becomes the new tail
        head->next = laterHead;
        //tail is now the head of reversed list
        return tail;
    }
};
