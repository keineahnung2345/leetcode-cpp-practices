//Runtime: 36 ms, faster than 18.01% of C++ online submissions for Palindrome Linked List.
//Memory Usage: 13.3 MB, less than 27.08% of C++ online submissions for Palindrome Linked List.

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
    bool isPalindrome(ListNode* head) {
        vector<int> v;
        ListNode* cur = head;
        while(cur){
            v.push_back(cur->val);
            cur = cur->next;
        }
        for(int i = 0; i < v.size()/2; i++){
            if(v[i] != v[v.size()-1-i]) return false;
        }
        return true;
    }
};

//https://leetcode.com/problems/palindrome-linked-list/discuss/64501/Java-easy-to-understand
//slow and fast pointer
//Runtime: 24 ms, faster than 98.19% of C++ online submissions for Palindrome Linked List.
//Memory Usage: 12.6 MB, less than 68.90% of C++ online submissions for Palindrome Linked List.

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
    bool isPalindrome(ListNode* head) {
        ListNode *slow = head, *fast = head;
        
        while(fast!=NULL && fast->next!=NULL){
            slow = slow->next;
            fast = fast->next->next;
        }
        
        if(fast != NULL){
            //the length of list is odd
            //in this situation we should ignore the middle node
            slow = slow->next;
        }
        
        //slow: later part of original list
        //fast: former part of original list
        slow = reverse(slow);
        fast = head;
        
        while(slow != NULL){
            if(slow->val != fast->val) return false;
            slow = slow->next;
            fast = fast->next;
        }
        
        return true;
    }
    
    ListNode* reverse(ListNode* head){
        //reverse the later part of original list
        ListNode* prev = NULL;
        ListNode* tmp;
        while(head != NULL){
            tmp = head->next;
            head->next = prev;
            prev = head;
            head = tmp;
        }
        //when the loop finishes, head is NULL, 
        //and prev is the last node in the original list
        return prev;
    }
};
