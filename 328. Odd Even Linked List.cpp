//Runtime: 20 ms, faster than 58.58% of C++ online submissions for Odd Even Linked List.
//Memory Usage: 10.1 MB, less than 8.57% of C++ online submissions for Odd Even Linked List.

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
    ListNode* oddEvenList(ListNode* head) {
        ListNode *oddHead = new ListNode(0); //virtual head
        ListNode *odd = oddHead;
        ListNode *evenHead = new ListNode(0); //virtual head
        ListNode *even = evenHead;
        ListNode *cur = head;
        int i = 1;
        
        while(cur){
            if(i % 2 == 1){
                odd->next = cur;
                odd = odd->next;
            }else{
                even->next = new ListNode(cur->val);
                even = even->next;
            }
            i++;
            cur = cur->next;
        }
        
        odd->next = evenHead->next;
        return oddHead->next;
    }
};

//Runtime: 12 ms, faster than 99.78% of C++ online submissions for Odd Even Linked List.
//Memory Usage: 10.3 MB, less than 8.57% of C++ online submissions for Odd Even Linked List.
//time: O(N), space: O(1)
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
    ListNode* oddEvenList(ListNode* head) {
        if(!head) return NULL;
        ListNode *odd = head, *even = head->next, *evenHead = even;
        while(even && even->next){
            //this loop stops when even->next is meaningless
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = evenHead;
        return head;
    }
};
