//https://leetcode.com/problems/reorder-list/discuss/44992/Java-solution-with-3-steps
//Runtime: 40 ms, faster than 72.72% of C++ online submissions for Reorder List.
//Memory Usage: 14.2 MB, less than 74.29% of C++ online submissions for Reorder List.
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
    void reorderList(ListNode* head) {
        //0 or 1 valid node
        if(!head || !head->next)
            return;
        
        //find the middle point
        /*
        for 1->2->3->4->5, now
        p1 points to 3, p2 points to 5
        for 1->2->3->4->5->6, now
        p1 points to 3, p2 points to 5
        */
        ListNode *p1 = head, *p2 = head;
        
        while(p2->next && p2->next->next){
            p1 = p1->next;
            p2 = p2->next->next;
        }
        
        //reverse the later half
        /*
        for 1->2->3->4->5, now
        1->2->3->5->4
        for 1->2->3->4->5->6, now
        1->2->3->6->5->4
        */
        ListNode *preMid = p1, *preCur = p1->next;
        while(preCur->next){
            ListNode* cur = preCur->next;
            // cout << "preCur->(cur->next): " << preCur->val << "->" << (cur->next ? cur->next->val : -1) <<endl;
            // cout << "cur->(preMid->next): " << cur->val << "->" << preMid->next->val << endl;
            // cout << "preMid->cur: " << preMid->val << "->" << cur->val << endl;
            
            /*
            at first iteration, cur is the 2nd node of later part
            in each iteration, 
            we move cur so it becomes the new head of later part
            in the loop, cur is 2nd node, then 3rd node, then 4th, ...
            */
            preCur->next = cur->next;
            cur->next = preMid->next;
            /*
            preMid serves as the previous node of later part,
            it will not be changed it this step
            preMid->next points to the head of later part
            */
            preMid->next = cur;
        }
        // cout << endl;
        
        //start reorder
        /*
        for 1->2->3->4->5,
        it becomes 1->2->3->5->4
        and then 1->5->2->4->3
        for 1->2->3->4->5->6,
        it becomes 1->2->3->6->5->4
        and then 1->6->2->3->5->4
        and then 1->6->2->5->3->4
        */
        p1 = head;
        p2 = preMid->next;
        
        while(p1 != preMid){
            /*
            p2 is the head of later part
            in each iteration, 
            move p2 to the behind of p1
            (p1 is initially the head of former part,
            but it will move)
            */
            // cout << "premid->(p2->next): " << preMid->val << "->" << (p2->next ? p2->next->val : -1) << endl;
            // cout << "p2->(p1->next): " << p2->val << "->" << p1->next->val << endl;
            // cout << "p1->p2: " << p1->val << "->" << p2->val << endl;
            preMid->next = p2->next;
            p2->next = p1->next;
            p1->next = p2;
            p1 = p2->next;
            p2 = preMid->next;
        }
    }
};
