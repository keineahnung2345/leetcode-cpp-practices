//Runtime: 132 ms, faster than 5.57% of C++ online submissions for Insertion Sort List.
//Memory Usage: 8.6 MB, less than 100.00% of C++ online submissions for Insertion Sort List.
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void swapValue(ListNode* a, ListNode* b){
        int tmp = a->val;
        a->val = b->val;
        b->val = tmp;
    };
    
    void insert(ListNode* list, ListNode* node){
        ListNode *cur = list, *prev, *tail;
        
        //find in list a node that just larger than node
        while(cur && cur->val <= node->val){
            prev = cur;
            cur = cur->next;
        }
        
        tail = list;
        while(tail->next){
            tail = tail->next;
        }
        
        // tail->next = node->next;
        prev->next = node;
        node->next = cur;
    };
    
    ListNode* insertionSortList(ListNode* head) {
        ListNode *newHead = new ListNode(INT_MIN);
        ListNode *node, *remaining = head;
        
        while(remaining){
            node = remaining;
            remaining = remaining->next;
            node->next = nullptr;
            insert(newHead, node);
        }
        
        return newHead->next;
    }
};
