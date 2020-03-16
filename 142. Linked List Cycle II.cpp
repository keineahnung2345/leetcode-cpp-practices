//Runtime: 20 ms, faster than 22.46% of C++ online submissions for Linked List Cycle II.
//Memory Usage: 11.2 MB, less than 16.67% of C++ online submissions for Linked List Cycle II.

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
    ListNode *detectCycle(ListNode *head) {
        set<ListNode*> visited;
        ListNode* cur = head;
        while(cur != NULL){
            if(visited.find(cur) != visited.end()){
                return cur;
            }else{
                visited.insert(cur);
            }
            cur = cur->next;
        }
        return NULL;
    }
};

//https://leetcode.com/problems/linked-list-cycle-ii/discuss/44793/O(n)-solution-by-using-two-pointers-without-change-anything
//Runtime: 12 ms, faster than 77.45% of C++ online submissions for Linked List Cycle II.
//Memory Usage: 9.2 MB, less than 100.00% of C++ online submissions for Linked List Cycle II.
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
    ListNode *detectCycle(ListNode *head) {
        if(!head || !head->next) return NULL;
        ListNode *slow = head, *fast = head;
        bool isCycle = false;
        
        /*
        slow : dist(slow) = dist(start to loop) + dist(loop to meet)
        fast : dist(fast) = dist(start to loop) + dist(loop to meet) + dist(meet to loop) + dist(loop to meet)
        because dist(slow)*2=dist(fast)
        */
        while(slow && fast){
            slow = slow->next;
            if(!fast->next) return NULL;
            fast = fast->next->next;
            if(slow == fast){
                isCycle = true;
                break;
            }
        }
        
        if(!isCycle){
            return NULL;
        }
        
        slow = head;
        /*
        now slow starts from head, and fast starts from meeting point
        and we know that dist(start to loop) equals to dist(meeting to loop)
        , so they will meet at loop
        */
        while(slow != fast){
            slow = slow->next;
            fast = fast->next;
        }
        
        return slow;
    }
};
