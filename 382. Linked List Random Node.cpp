//Runtime: 36 ms, faster than 88.32% of C++ online submissions for Linked List Random Node.
//Memory Usage: 14.4 MB, less than 100.00% of C++ online submissions for Linked List Random Node.
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
    vector<int> v;
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head) {
        ListNode* cur = head;
        while(cur){
            v.push_back(cur->val);
            cur = cur->next;
        }
    }
    
    /** Returns a random node's value. */
    int getRandom() {
        return v[rand()%v.size()];
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */
 
