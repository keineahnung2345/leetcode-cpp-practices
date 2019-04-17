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
