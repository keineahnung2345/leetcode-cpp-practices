/**
Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

Example:

Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4
**/

//Runtime: 8 ms, faster than 100.00% of C++ online submissions for Merge Two Sorted Lists.
//Memory Usage: 8.9 MB, less than 100.00% of C++ online submissions for Merge Two Sorted Lists.
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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == NULL) return l2;
        if(l2 == NULL) return l1;
        //let the list with smaller head be cur1
        ListNode *h, *cur1, *cur2;
        if(l1->val <= l2->val){
            h = cur1 = l1;
            cur2 = l2;
        }else{
            h = cur1 = l2;
            cur2 = l1;
        }
        if(cur1->next == NULL){
            cur1->next = cur2;
            return cur1;
        }
        //stop when one of the list ends
        while(cur2 != NULL && cur1 != NULL){
            // cout << cur1->val << " " << cur2->val << endl;
            if(cur1->next == NULL){
                cur1->next = cur2;
                //done processing first list
                cur1 = NULL;
            }else if(cur2->val <= cur1->next->val){
                //merge cur2 into l1 and move cur2
                ListNode* tmp = cur1->next;
                cur1->next = cur2;
                cur2 = cur2->next;
                cur1->next->next = tmp;
            }else{
                //move cur1 to the next
                cur1 = cur1->next;
            }
        }
        return h;
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
