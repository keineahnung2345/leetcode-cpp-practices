//Approach 1: Brute Force
//time: O(NlogN), collect all nodes and then sort
//space: O(N)

//Approach 2: Compare the head of linked list
//time: O(KN), k: #linked list
//space: O(N) -> O(1) if in-place

//Approach 3: Optimize Approach 2 by Priority Queue
//Runtime: 36 ms, faster than 64.12% of C++ online submissions for Merge k Sorted Lists.
//Memory Usage: 12 MB, less than 71.35% of C++ online submissions for Merge k Sorted Lists.
//time: O(NlogK)
//space: O(K) for the priority queue
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

//recursion
//https://leetcode.com/problems/merge-two-sorted-lists/discuss/9715/Java-1-ms-4-lines-codes-using-recursion
//Runtime: 8 ms, faster than 71.22% of C++ online submissions for Merge Two Sorted Lists.
//Memory Usage: 14.3 MB, less than 94.06% of C++ online submissions for Merge Two Sorted Lists.
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == nullptr) return l2;
        if(l2 == nullptr) return l1;
        if(l1->val <= l2->val){
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }else{
            l2->next = mergeTwoLists(l2->next, l1);
            return l2;
        }
    }
};

//iterative
//https://leetcode.com/problems/merge-two-sorted-lists/discuss/9735/Python-solutions-(iteratively-recursively-iteratively-in-place).
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Merge Two Sorted Lists.
//Memory Usage: 14.5 MB, less than 55.22% of C++ online submissions for Merge Two Sorted Lists.
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *head = new ListNode(-1);
        ListNode *cur = head;
        
        while(l1 != nullptr && l2 != nullptr){
            if(l1->val <= l2->val){
                cur->next = l1;
                l1 = l1->next;
            }else{
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        
        if(l1 != nullptr) cur->next = l1;
        else if(l2 != nullptr) cur->next = l2;
        
        return head->next;
    }
};
