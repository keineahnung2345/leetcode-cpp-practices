//Runtime: 12 ms, faster than 13.34% of C++ online submissions for Partition List.
//Memory Usage: 10.6 MB, less than 14.01% of C++ online submissions for Partition List.
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
    ListNode* partition(ListNode* head, int x) {
        ListNode *smallhead, *largehead;
        smallhead = new ListNode(-1);
        largehead = new ListNode(-1);
        
        ListNode *cur = head;
        ListNode *smallcur = smallhead, *largecur = largehead;
        
        while(cur){
            if(cur->val < x){
                smallcur->next = cur;
                smallcur = smallcur->next;
            }else{
                largecur->next = cur;
                largecur = largecur->next;
            }
            cur = cur->next;
        }
        
        largecur->next = nullptr;
        smallcur->next = largehead->next;
        
        return smallhead->next;
    }
};
