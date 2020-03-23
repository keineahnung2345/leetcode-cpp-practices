//Runtime: 68 ms, faster than 32.71% of C++ online submissions for Sort List.
//Memory Usage: 12.7 MB, less than 27.50% of C++ online submissions for Sort List.
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
//     void merge(ListNode* a, ListNode* b){
//         ListNode *newHead = new ListNode(0);
//         ListNode *cur = newHead;
        
//         while(a && b){
//             if(a->val <= b.val){
//                 cur->val = a->val;
//                 a = a->next;
//             }else
//                 cur->val = b->val;
//                 b = b->next;
//             }
//         }
        
//         if(a){
//             cur->next = a;
//         }else if(b){
//             cur->next = b;
//         }

//         return newHead;
//     };
    
    ListNode* sortList(ListNode* head) {
        if(!head) return head;
        vector<int> arr;
        ListNode* cur = head;
        
        while(cur){
            arr.push_back(cur->val);
            cur = cur->next;
        }
        
        sort(arr.begin(), arr.end());
        
        cur = head;
        int i = 0;
        while(cur){
            cur->val = arr[i++];
            cur = cur->next;
        }
        
        return head;
    }
};
