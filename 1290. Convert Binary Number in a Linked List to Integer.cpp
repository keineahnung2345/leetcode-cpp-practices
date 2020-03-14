//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Convert Binary Number in a Linked List to Integer.
//Memory Usage: 7.8 MB, less than 100.00% of C++ online submissions for Convert Binary Number in a Linked List to Integer.

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
    int getDecimalValue(ListNode* head) {
        int ans = 0;
        ListNode* cur = head;
        
        while(cur){
            ans = (ans << 1) + cur->val;
            cur = cur->next;
        }
        
        return ans;
    }
};
