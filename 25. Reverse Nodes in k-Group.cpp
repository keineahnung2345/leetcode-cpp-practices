//Runtime: 20 ms, faster than 39.60% of C++ online submissions for Reverse Nodes in k-Group.
//Memory Usage: 10.3 MB, less than 16.67% of C++ online submissions for Reverse Nodes in k-Group.
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
    void reverseTwoNodes(ListNode** a, ListNode** b){
        //a and b are pointer of pointer
        //a->x->... and b->y->... to b->a->x->... and y->...
        // cout << "reverse: " << (*a)->val << " and " << (*b)->val << endl;
        ListNode* latter = (*b)->next;
        (*b)->next = *a;
        //a->(b) and b->y->... to b->a->y->...
        if((*a)->next == *b) (*a)->next = nullptr;
        *a = *b;
        *b = latter;
        // cout << "reversed: " << ((*a) ? (*a)->val : -1) << " and " << ((*b) ? (*b)->val : -1) << endl;
    };
    
    ListNode* reverseKGroup(ListNode* head, int k) {
        //check if the length of list >= k
        ListNode* tail = head;
        //go forward for k-1 steps
        for(int i = 0; i < k-1 && tail; ++i){
            tail = tail->next;
        }
        //the list's length < k, don't need to reverse it
        if(!tail) return head;
        
        //reverse the first k node and call function for rest nodes
        ListNode* laterHead = reverseKGroup(tail->next, k);
        
        // cout << "head: " << head->val << ", tail: " << tail->val << endl;
        ListNode *cur = head, *next = head->next;
        //each time reverse two nodes, reverse for k-1 times
        for(int i = 0; i < k-1; ++i){
            reverseTwoNodes(&cur, &next);
        }
        
        // cout << "new head: " << tail->val << ", new tail: " << head->val << endl;
        // cout << "the reversed group: ";
        // cur = tail;
        // while(cur){
        //     cout << cur->val << " ";
        //     cur = cur->next;
        // }
        // cout << endl;
        
        //original head of group now becomes the new tail
        head->next = laterHead;
        //tail is now the head of reversed list
        return tail;
    }
};

//recursion
//https://leetcode.com/problems/reverse-nodes-in-k-group/discuss/11423/Short-but-recursive-Java-code-with-comments
//Runtime: 24 ms, faster than 26.27% of C++ online submissions for Reverse Nodes in k-Group.
//Memory Usage: 10.1 MB, less than 77.96% of C++ online submissions for Reverse Nodes in k-Group.
//space: O(n/k) used by recursion stack
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* cur = head;
        
        int steps = 0;
        
        for(; steps < k && cur; ++steps){
            cur = cur->next;
        }
        
        //list's length < k, don't need to reverse
        if(steps < k) return head;
        
        //now cur is the head of next group, reverse that group first
        cur = reverseKGroup(cur, k);
        
        /*
        123456, k = 3
        assume the later group is already reversed: 123654
        head: 1, cur: 6
        "head" is the head of list to be reversed, 
        and it should be connected to the head of reversed list,
        so we set head->next to "cur"
        tmp: 2, head->next: 6,
        and later do the following:
        cur: 1, head: 2
        so that cur is still the head of reversed list and
        "head" is still the head of the list to be reversed
        
        we do this for k times,
        tmp: 3, head->next: 1, cur: 2, head: 3
        tmp: nullptr, head->next: 2, cur: 3, head: nullptr
        
        to summary, in each iteration,
        we cut the head of forward list and append it to the head of reversed list,
        and this process is done for k times,
        meaning cutting for k times and appending for k times
        */
        for(int i = 0; i < k; ++i){
            //"head": head of the list to be reversed
            ListNode* tmp = head->next;
            //cur: head of reversed list
            head->next = cur;
            cur = head;
            head = tmp;
        }
        
        return cur;
    }
};

//non-recursive
//https://leetcode.com/problems/reverse-nodes-in-k-group/discuss/11440/Non-recursive-Java-solution-and-idea
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
    ListNode* reverseOneGroup(ListNode* head_prev, ListNode* tail_next){
        //head_prev: the node before current group's head
        //tail_prev: the node after current group's tail
        /**
         * Reverse a link list between begin and end exclusively
         * an example:
         * a linked list:
         * 0->1->2->3->4->5->6
         * |           |   
         * begin       end
         * after call begin = reverse(begin, end)
         * 
         * 0->3->2->1->4->5->6
         *          |  |
         *      begin end
         * @return the reversed list's 'begin' node, 
         which is the precedence of node end
         */
        ListNode* cur = head_prev->next;
        ListNode* new_head_prev = cur;
        ListNode* prev = head_prev;
        ListNode* next;
        /*
        0->1->2->3->4, begin: 0, end: 4, cur: 1
        1->0
        2->1->0
        3->2->1->0
        prev: the previous node of cur
        next: the next node of cur
        */
        while(cur != tail_next){
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        
        /*
        now:
        prev: 3, cur: 4
        */
        head_prev->next = prev;
        new_head_prev->next = cur;
        
        return new_head_prev;
    };
    
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(!head || !head->next || k == 1) return head;
        
        ListNode* dummy_head = new ListNode(-1);
        dummy_head->next = head;
        ListNode* group_head_prev = dummy_head;
        
        for(int i = 1; head; ++i){
            if(i%k == 0){
                /*
                for 12345, k = 3, 
                it will reverse the first group when head points to 3,
                at that time,
                group_head_prev is 0, head->next is 4
                */
                group_head_prev = reverseOneGroup(group_head_prev, head->next);
                head = group_head_prev->next;
            }else{
                head = head->next;
            }
        }
        
        return dummy_head->next;
    }
};
