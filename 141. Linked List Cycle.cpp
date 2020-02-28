//Runtime: 812 ms, faster than 9.19% of C++ online submissions for Linked List Cycle.
//Memory Usage: 11.4 MB, less than 23.68% of C++ online submissions for Linked List Cycle.

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
    bool hasCycle(ListNode *head) {
        set<ListNode*> seen;
        ListNode* cur = head;
        
        while(cur != NULL){
            // cout << cur->val << " ";
            if(find(seen.begin(), seen.end(), cur) == seen.end())
                seen.insert(cur);
            else
                return true;
            cur = cur->next;
        }
        cout <<endl;
        
        return false;
    }
};
