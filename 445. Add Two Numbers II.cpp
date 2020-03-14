//Runtime: 24 ms, faster than 93.79% of C++ online submissions for Add Two Numbers II.
//Memory Usage: 11.6 MB, less than 51.85% of C++ online submissions for Add Two Numbers II.

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        vector<int> v1, v2;
        ListNode* cur = l1;
        while(cur){
            v1.insert(v1.begin(), cur->val);
            cur = cur->next;
        }
        
        cur = l2;
        while(cur){
            v2.insert(v2.begin(), cur->val);
            cur = cur->next;
        }
        
        //reverse room for carry-in
        int newSize = max(v1.size(), v2.size()) + 1;
        v1.resize(newSize);
        v2.resize(newSize);
        for(int i = 0; i < newSize-1; i++){
            v1[i] += v2[i];
            if(v1[i] >= 10){
                v1[i]-=10;
                v1[i+1]++;
            }
            // cout << v1[i] << " ";
        }
        // cout << endl;
        
        ListNode* head = new ListNode();
        cur = head;
        //skip leading 0s
        int idx = newSize-1;
        // cout << "idx: " << idx << endl;
        while(idx >= 0 && v1[idx] == 0){
            idx--;
        }
        // cout << "idx: " << idx << endl;
        for(; idx >= 0; idx--){
            cur->val = v1[idx];
            if(idx > 0){
                //not the last node
                cur->next = new ListNode();
                cur = cur->next;
            }
        }
        
        return head;
    }
};

//Stack
//Runtime: 32 ms, faster than 54.73% of C++ online submissions for Add Two Numbers II.
//Memory Usage: 13.7 MB, less than 22.22% of C++ online submissions for Add Two Numbers II.
//time: O(n)

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> stk1, stk2;
        ListNode* cur = l1;
        while(cur){
            stk1.push(cur->val);
            cur = cur->next;
        }
        
        cur = l2;
        while(cur){
            stk2.push(cur->val);
            cur = cur->next;
        }
        
        ListNode* head = new ListNode(0);
        int d = 0;
        
        while(!stk1.empty() || !stk2.empty()){
            if(!stk1.empty()){
                d += stk1.top();
                stk1.pop();
            }
            if(!stk2.empty()){
                d += stk2.top();
                stk2.pop();
            }
            head->val = d%10;
            ListNode* prehead = new ListNode(d/10);
            prehead->next = head;
            head = prehead;
            d = d/10;
        }
        
        return head->val == 0 ? head->next : head;
    }
};
