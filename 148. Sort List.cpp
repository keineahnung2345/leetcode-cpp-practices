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

//merge sort
//https://leetcode.com/problems/sort-list/discuss/46714/Java-merge-sort-solution
//use new
//Runtime: 124 ms, faster than 16.37% of C++ online submissions for Sort List.
//Memory Usage: 48.8 MB, less than 5.00% of C++ online submissions for Sort List.
//don't use new to speed up
//Runtime: 72 ms, faster than 26.62% of C++ online submissions for Sort List.
//Memory Usage: 26.7 MB, less than 5.00% of C++ online submissions for Sort List.
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
    ListNode* merge(ListNode* a, ListNode* b){
        ListNode *newHead = new ListNode(0);
        ListNode *cur = newHead;
        
        // cout << "in merge a: " << endl;
        cur = a;
        while(cur){
            // cout << cur->val << " ";
            cur = cur->next;
        }
        // cout << endl;
        
        // cout << "in merge b: " << endl;
        // cur = b;
        // while(cur){
        //     cout << cur->val << " ";
        //     cur = cur->next;
        // }
        // cout << endl;
        
        cur = newHead;
        
        // cout << "building list: " << endl;
        while(a && b){
            if(a->val <= b->val){
                //use new -> time and space specified in first two rows
                // cur->next = new ListNode(a->val);
                //not use new -> time and space specified in second two rows
                cur->next = a;
                // cout << a->val << " ";
                a = a->next;
            }else{
                // cur->next = new ListNode(b->val);
                cur->next = b;
                // cout << b->val << " ";
                b = b->next;
            }
            cur = cur->next;
        }
        
        //Method 1 to add remaining list
//         while(a){
//             cur->next = new ListNode(a->val);
//             cout << a->val << " ";
//             a = a->next;
//             cur = cur->next;
//         }
        
//         while(b){
//             cur->next = new ListNode(b->val);
//             cout << b->val << " ";
//             b = b->next;
//             cur = cur->next;
//         }
        
        //Method 2 to add remaining list
        if(a){
            cur->next = a;
        }else if(b){
            cur->next = b;
        }
        
        // cout << endl;
        
        // cout << "list built: " << endl;
        // cur = newHead->next;
        // while(cur){
        //     cout << cur->val << " ";
        //     cur = cur->next;
        // }
        // cout << endl;

        return newHead->next;
    };
    
    ListNode* sortList(ListNode* head) {
        //length 0 or length 1, we cannot split anymore
        if(!head || !head->next) return head;
        
        // cout << "current list: " << endl;
        ListNode* cur = head;
        while(cur){
            // cout << cur->val << " ";
            cur = cur->next;
        }
        // cout << endl;
        
        //split list
        ListNode *slow = head, *fast = head;
        ListNode *slowPrev; //used to cut the list into half
        
        while(fast && fast->next){
            slowPrev = slow;
            
            slow = slow->next;
            fast = fast->next->next;
        }
        
        /*
        now "head" and "slow" are the head of two lists,
        we need to split them by setting "slow"'s previous node's next to nullptr
        */
        slowPrev->next = nullptr;
        
        //sort the splitted lists
        head = sortList(head);
        slow = sortList(slow);
        
        return merge(head, slow);
    }
};
