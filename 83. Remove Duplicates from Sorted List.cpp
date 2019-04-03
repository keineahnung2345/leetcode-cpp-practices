//Runtime: 12 ms, faster than 100.00% of C++ online submissions for Remove Duplicates from Sorted List.
//Memory Usage: 9.2 MB, less than 65.42% of C++ online submissions for Remove Duplicates from Sorted List.

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
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL || head->next == NULL) return head;
        
        ListNode* last = head;
        ListNode* cur = head->next;
        
        while(cur != NULL){
            if(cur->val == last->val){
                //remove cur
                last->next = cur->next;
            }else{
                //update last only if cur isn't duplicate
                last = cur;
            }
            cur = cur->next;
        }
        
        return head;
    }
};

/**
Approach 1: Straight-Forward Approach
**/

/**
Time: O(n)
Space: O(1)
**/

/**
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* cur = head;
        while(!cur && !cur->next){
            if(cur->val == cur->next->val){
                //remove cur->next
                cur->next = cur->next->next;
                //next time we compare cur and cur->next(which was cur->next->next)
            }else{
                cur = cur->next;
            }
        }
        return head;
    }
};
**/
