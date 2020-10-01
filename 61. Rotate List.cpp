//Runtime: 8 ms, faster than 81.03% of C++ online submissions for Rotate List.
//Memory Usage: 11.9 MB, less than 20.29% of C++ online submissions for Rotate List.
//time: O(N), space: O(1)
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
    ListNode* rotateRight(ListNode* head, int k) {
        ListNode *slow = head, *fast = head;
        int len = 0;
        
        for(ListNode* cur = head; cur; cur = cur->next) ++len;
        
        if(len <= 1) return head;
        
        k = k % len;
        if(k == 0) return head;
        
        for(int i = 0; i < k; ++i) fast = fast->next;
        
        while(slow->next && fast->next){
            slow = slow->next;
            fast = fast->next;
        }
        
        //now slow is the previous node of the new head
        ListNode* newhead = slow->next;
        slow->next = nullptr;
        //fast is the last node of original list
        fast->next = head;
        
        return newhead;
    }
};
