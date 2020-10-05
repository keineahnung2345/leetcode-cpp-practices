//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Reverse Linked List II.
//Memory Usage: 7.8 MB, less than 18.66% of C++ online submissions for Reverse Linked List II.
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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if(!head || !head->next) return head;
        
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* cur = dummy;
        ListNode* pre;
        ListNode *rdummy = new ListNode(-1), *rtail, *rcur;
        
        //start from dummy because we need the previous node of reversed list
        for(int i = 0; cur; ++i){
            // cout << i << ": " << cur->val << endl;
            ListNode* next = cur->next;
            if(i == m-1){
                //the previous node of reversed list
                pre = cur;
            }else if(i >= m && i <= n){
                if(i == m) rtail = cur;
                //prepend cur to the head of reversed list
                cur->next = rdummy->next;
                rdummy->next = cur;
                //connect reversed list's tail with the org list
                if(i == n){
                    rtail->next = next;
                    break;
                }
            }
            cur = next;
        }
        
        //connect reversed list's head with the org list
        pre->next = rdummy->next;
        
        return dummy->next;
    }
};
