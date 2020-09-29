//linked list
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Remove Nth Node From End of List.
//Memory Usage: 11 MB, less than 11.61% of C++ online submissions for Remove Nth Node From End of List.
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* cur = head;
        int len = 0;
        
        while(cur){
            ++len;
            cur = cur->next;
        }
        
        if(n == len){
            //delete the head
            ListNode* ans = head->next;
            delete head;
            return ans;
        }
        
        cur = head;
        for(int i = 0; i < len; ++i){
            if(i == len-n-1){
                //the node previous to the node to be deleted
                ListNode* to_delete = cur->next;
                cur->next = cur->next->next;
                delete to_delete;
                break;
            }
            cur = cur->next;
        }
        
        return head;
    }
};

//Approach 1: Two pass algorithm
//use dummy head to avoid corner case
//Runtime: 8 ms, faster than 35.30% of C++ online submissions for Remove Nth Node From End of List.
//Memory Usage: 10.9 MB, less than 18.24% of C++ online submissions for Remove Nth Node From End of List.
//time: O(L), space: O(1)
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode();
        dummy->next = head;
        
        ListNode* cur;
        int len = 0;
        
        cur = dummy->next;
        while(cur){
            ++len;
            cur = cur->next;
        }
        
        // cout << "len: " << len << endl;
        
        cur = dummy;
        for(int i = 0; i < len; ++i, cur = cur->next){
            //i is 1-based
            // cout << i << " : " << cur->val << endl;
            if(i == len-n){
                //this is the node previous to the node to be deleted
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
                break;
            }
        }
        
        return dummy->next;
    }
};
