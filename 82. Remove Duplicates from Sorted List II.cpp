//two pointer
//Runtime: 8 ms, faster than 93.49% of C++ online submissions for Remove Duplicates from Sorted List II.
//Memory Usage: 11.5 MB, less than 15.28% of C++ online submissions for Remove Duplicates from Sorted List II.
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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* dummy = new ListNode(-1);
        
        dummy->next = head;
        
        ListNode *slow = dummy, *fast = head;
        
        while(fast){
            bool dup = false;
            do{
                //assume fast's val is not duplicate
                dup = false;
                while(fast && fast->next && fast->val == fast->next->val){
                    fast = fast->next;
                    dup = true;
                }
                //if fast's val is duplicate, we discard it and find from next
                if(dup) fast = fast->next;
                // cout << "fast: " << fast->val << endl;
            }while(dup);
            //now fast is nullptr or it points to non-duplicate value
            
            // cout << slow->val << " <- " << fast->val << endl;
            slow->next = fast;
            slow = slow->next;
            //need to check if fast is nullptr
            if(fast) fast = fast->next;
        }
        
        return dummy->next;
    }
};
