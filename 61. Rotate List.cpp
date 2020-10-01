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

//cleaner
//https://leetcode.com/problems/rotate-list/discuss/22735/My-clean-C%2B%2B-code-quite-standard-(find-tail-and-reconnect-the-list)
//Runtime: 8 ms, faster than 81.03% of C++ online submissions for Rotate List.
//Memory Usage: 12 MB, less than 14.57% of C++ online submissions for Rotate List.
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head || !head->next || k == 0) return head;
        ListNode* cur = head;
        int len = 1;
        
        //find tail
        while(cur->next){
            ++len;
            cur = cur->next;
        }
        //now cur is the last node of original list
        
        //connect tail and head
        cur->next = head;
        
        //find the tail of new list
        for(int i = 0; i < len - (k%len); ++i){
            cur = cur->next;
        }
        
        //head of new list is the next node of tail of new list
        head = cur->next;
        cur->next = nullptr;
        
        return head;
    }
};
