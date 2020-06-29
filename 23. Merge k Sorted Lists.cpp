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

//Approach 4: Merge lists one by one
//extended from "21. Merge Two Sorted Lists"
//Runtime: 248 ms, faster than 14.96% of C++ online submissions for Merge k Sorted Lists.
//Memory Usage: 12.1 MB, less than 61.91% of C++ online submissions for Merge k Sorted Lists.
//time: O(KN), space: O(1)
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
    };
    
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *head = nullptr;
        
        for(int i = 0; i < lists.size(); ++i){
            head = mergeTwoLists(head, lists[i]);
        }
        
        return head;
    }
};

//Approach 5: Merge with Divide And Conquer
//Runtime: 16 ms, faster than 99.77% of C++ online submissions for Merge k Sorted Lists.
//Memory Usage: 12.3 MB, less than 40.56% of C++ online submissions for Merge k Sorted Lists.
//time: O(NlogK), space: O(1)
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
    };
    
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        if(n == 0) return nullptr;
        
        int interval = 1;
        
        /*
        divide and conquer
        l0, l1, l2, l3, l4, l5
        -> new l0(l0+l1), new l2(l2+l3), new l4(l4+l5)
        -> new l0(l0+l2), l4
        -> new l0(l0+l4)
        */
        while(interval < n){
            for(int i = 0; i+interval < n; i += interval*2){
                lists[i] = mergeTwoLists(lists[i], lists[i+interval]);
            }
            interval *= 2;
        }
        
        return lists[0];
    }
};
