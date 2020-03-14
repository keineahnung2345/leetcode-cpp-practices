//Runtime: 20 ms, faster than 58.58% of C++ online submissions for Odd Even Linked List.
//Memory Usage: 10.1 MB, less than 8.57% of C++ online submissions for Odd Even Linked List.

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
    ListNode* oddEvenList(ListNode* head) {
        ListNode *oddHead = new ListNode(0); //virtual head
        ListNode *odd = oddHead;
        ListNode *evenHead = new ListNode(0); //virtual head
        ListNode *even = evenHead;
        ListNode *cur = head;
        int i = 1;
        
        while(cur){
            if(i % 2 == 1){
                odd->next = cur;
                odd = odd->next;
            }else{
                even->next = new ListNode(cur->val);
                even = even->next;
            }
            i++;
            cur = cur->next;
        }
        
        odd->next = evenHead->next;
        return oddHead->next;
    }
};
