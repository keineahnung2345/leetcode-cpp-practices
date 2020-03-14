//Runtime: 12 ms, faster than 74.84% of C++ online submissions for Split Linked List in Parts.
//Memory Usage: 9.9 MB, less than 9.09% of C++ online submissions for Split Linked List in Parts.
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
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        //hint: If there are N nodes in the list, and k parts, then every part has N/k elements, except the first N%k parts have an extra one.
        vector<int> inputs;
        ListNode* cur = root;
        while(cur){
            inputs.push_back(cur->val);
            cur = cur->next;
        }
        
        //cumulative size for each part
        vector<int> parts(k);
        for(int i = 0; i < k; i++){
            parts[i] = inputs.size()/k + (i < inputs.size()%k) + ((i>0) ? parts[i-1] : 0);
        }
        
        //need to "new ListNode" in a loop!
        //if "new" while initilaizing vector, all the elements point to the same position
        // vector<ListNode*> ans(k, new ListNode(0));
        vector<ListNode*> ans(k, NULL);
        for(int i = 0; i < k; i++){
            if((i > 0 && parts[i] - parts[i-1] == 0) || parts[i] == 0){
                ans[i] = NULL;
            }else{
                ans[i] = new ListNode(-1);
            }
        }
        
        vector<ListNode*> tails(k);
        for(int i = 0; i < k; i++){
            tails[i] = ans[i];
        }
        
        int partId = 0;
        for(int i = 0; i < inputs.size(); i++){
            if(i >= parts[partId]){
                partId++;
            }
            tails[partId]->val = inputs[i];
            if(i+1 < parts[partId]){
                tails[partId]->next = new ListNode(0);
                tails[partId] = tails[partId]->next;
            }
        }
        
        return ans;
    }
};
