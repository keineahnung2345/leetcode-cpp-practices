//Hint 1: We can use a stack that stores nodes in monotone decreasing order of value. When we see a node_j with a larger value, every node_i in the stack has next_larger(node_i) = node_j .
//Runtime: 208 ms, faster than 84.96% of C++ online submissions for Next Greater Node In Linked List.
//Memory Usage: 25.5 MB, less than 58.82% of C++ online submissions for Next Greater Node In Linked List.
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
    vector<int> nextLargerNodes(ListNode* head) {
        ListNode* cur = head;
        vector<int> inputs;
        while(cur){
            inputs.push_back(cur->val);
            cur = cur->next;
        }
        
        vector<int> ans(inputs.size(), 0);
        stack<int> stk;
        
        for(int i = 0; i < inputs.size(); i++){
            //stk's elements are in decreasing order
            //pop all elements <= inputs[i] and set their corresponding ans
            //the other elements remains in the stack
            while(!stk.empty() && inputs[i] > inputs[stk.top()]){
                ans[stk.top()] = inputs[i];
                stk.pop();
            }
            stk.push(i);
        }
        
        return ans;
    }
};
