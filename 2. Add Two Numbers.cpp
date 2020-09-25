//Runtime: 32 ms, faster than 79.81% of C++ online submissions for Add Two Numbers.
//Memory Usage: 71.1 MB, less than 26.28% of C++ online submissions for Add Two Numbers.
//time: O(max(m,n)), space: O(max(m,n))
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *prehead = new ListNode();
        ListNode *pre = prehead;
        ListNode *cur1 = l1, *cur2 = l2;
        int digit = 0;
        
        while(cur1 || cur2 || digit > 0){
            if(cur1){
                digit += cur1->val;
                cur1 = cur1->next;
            }
            if(cur2){
                digit += cur2->val;
                cur2 = cur2->next;
            }
            ListNode *tmp = new ListNode(digit%10);
            pre->next = tmp;
            pre = pre->next;
            digit/=10;
        }
        
        return prehead->next;
    }
};

//Follow up
//What if the the digits in the linked list are stored in non-reversed order? For example:
//(3 -> 4 -> 2) + (4 -> 6 -> 5) = 8 -> 0 -> 7
//reverse l1 and l2 first, do the algo, and then reverse the answer
//reverse function:
ListNode* reverse(ListNode* h){
    if(!h || !h->next) return h;

    ListNode* prev = nullptr;
    ListNode* cur = h;
    while(cur){
        ListNode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    return prev;
}
