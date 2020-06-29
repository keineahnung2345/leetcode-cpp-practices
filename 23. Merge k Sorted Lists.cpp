//Runtime: 36 ms, faster than 64.12% of C++ online submissions for Merge k Sorted Lists.
//Memory Usage: 12 MB, less than 71.35% of C++ online submissions for Merge k Sorted Lists.
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto comp = [](const ListNode* a, const ListNode* b){
            return a->val > b->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(comp)> pq(comp);
        
        for(ListNode* node : lists){
            if(node != nullptr) pq.push(node);
        }
        
        ListNode* head = new ListNode(-1);
        ListNode* cur = head;
        
        while(!pq.empty()){
            ListNode* node = pq.top(); pq.pop();
            cur->next = node;
            node = node->next;
            cur = cur->next;
            cur->next = nullptr;
            if(node != nullptr){
                pq.push(node);
            }
        }
        
        return head->next;
    }
};
