//iteration
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Reverse Linked List II.
//Memory Usage: 7.8 MB, less than 18.66% of C++ online submissions for Reverse Linked List II.
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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if(!head || !head->next) return head;
        
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* cur = dummy;
        ListNode* pre;
        ListNode *rdummy = new ListNode(-1), *rtail, *rcur;
        
        //start from dummy because we need the previous node of reversed list
        for(int i = 0; cur; ++i){
            // cout << i << ": " << cur->val << endl;
            ListNode* next = cur->next;
            if(i == m-1){
                //the previous node of reversed list
                pre = cur;
            }else if(i >= m && i <= n){
                if(i == m) rtail = cur;
                //prepend cur to the head of reversed list
                cur->next = rdummy->next;
                rdummy->next = cur;
                //connect reversed list's tail with the org list
                if(i == n){
                    rtail->next = next;
                    break;
                }
            }
            cur = next;
        }
        
        //connect reversed list's head with the org list
        pre->next = rdummy->next;
        
        return dummy->next;
    }
};

//Approach 2: Iterative Link Reversal.
//Runtime: 4 ms, faster than 64.33% of C++ online submissions for Reverse Linked List II.
//Memory Usage: 7.9 MB, less than 5.08% of C++ online submissions for Reverse Linked List II.
//time: O(N), space: O(1)
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;
        
        ListNode *prev = dummy, *cur = head;
        
        //move cur "m-1" steps forward, so it become the mth node
        int i = 1;
        for(; i < m; ++i){
            prev = prev->next;
            cur = cur->next;
        }
        
        //rdummy: the previous node of the head of reversed list
        ListNode *rdummy = prev;
        //rtail: the tail of reversed list
        ListNode *rtail = cur;
        
        //do n-m+1 times, moving "cur" from mth node to (n+1)th node
        //m -> (m-1), (m+1) -> m, ..., n->(n-1)
        for(; i <= n; ++i){
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        
        //prev is the tail of reversed list
        rdummy->next = prev;
        //cur is the next node of the tail of reversed list
        rtail->next = cur;
        
        return dummy->next;
    }
};

//recursion
//https://leetcode.com/problems/reverse-linked-list-ii/solution/242639
//time: O(N)
//space: O(N), space used by recursion
//for reverse the whole list, check https://github.com/keineahnung2345/leetcode-cpp-practices/blob/master/206.%20Reverse%20Linked%20List.cpp
class Solution {
public:
    ListNode* successor;

    ListNode* reverseN(ListNode* head, int n){
        if(n == 1){
            //successor: the node after the first n nodes
            successor = head->next;
            return head;
        }

        ListNode* rhead = reverseN(head->next, n-1);

        //head is now the new tail of reversed list
        head->next->next = head;
        head->next = successor;

        return rhead;
    }
    
    ListNode* reverseBetween(ListNode* head, int m, int n){
        if(m == 1){
            return reverseN(head, n);
        }

        head->next = reverseBetween(head->next, m-1, n-1);

        return head;
    }
};
