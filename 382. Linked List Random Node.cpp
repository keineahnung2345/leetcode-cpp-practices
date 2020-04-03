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
 
//Reservoir sampling
//https://leetcode.com/problems/linked-list-random-node/discuss/85662/Java-Solution-with-cases-explain
//Runtime: 40 ms, faster than 60.00% of C++ online submissions for Linked List Random Node.
//Memory Usage: 14 MB, less than 100.00% of C++ online submissions for Linked List Random Node.
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
    ListNode *head;
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head) {
        this->head = head;
    }
    
    /** Returns a random node's value. */
    int getRandom() {
        ListNode *cur = head, *candidate = head;
        int count = 0;
        while(cur != nullptr){
            if(rand()%(count+1) == count){
                //select the (k+1) th element with prob = 1/(k+1)
                candidate = cur;
            }
            cur = cur->next;
            count++;
        }
        return candidate->val;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */
