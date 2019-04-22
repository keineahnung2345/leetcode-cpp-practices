//Runtime: 52 ms, faster than 98.21% of C++ online submissions for Intersection of Two Linked Lists.
//Memory Usage: 19.1 MB, less than 14.04% of C++ online submissions for Intersection of Two Linked Lists.

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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        vector<ListNode*> lA, lB;
        ListNode *curA = headA, *curB = headB;
        
        while(curA){
            lA.push_back(curA);
            curA = curA->next;
        }
        
        while(curB){
            lB.push_back(curB);
            curB = curB->next;
        }
        
        int i = 0;
        while(i < min(lA.size(), lB.size())){
            if(lA[lA.size()-1-i] != lB[lB.size()-1-i]){
                break;
            }
            i++;
        }
        
        if(i == 0) return NULL;
        return lA[lA.size()-1-(i-1)];
    }
};

//https://leetcode.com/problems/intersection-of-two-linked-lists/discuss/49785/Java-solution-without-knowing-the-difference-in-len!
//Two pointers
//time: O(m+n), space: O(1)
//Runtime: 52 ms, faster than 98.21% of C++ online submissions for Intersection of Two Linked Lists.
//Memory Usage: 16.8 MB, less than 41.28% of C++ online submissions for Intersection of Two Linked Lists.

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == NULL || headB == NULL) return NULL;
        
        ListNode *pA = headA, *pB = headB;
        
        //if length of A and B are different, we will stop at 2nd iteration
        while(pA != pB){
            //if the first list ends, we reset the pointer to the head of another list
            pA = (pA == NULL)?headB:pA->next;
            pB = (pB == NULL)?headA:pB->next;
        }
        /**
        given 
        A = [4,8,4,5], 
        B = [5,0,8,4,5]
        in the 1st iteration pA go through 1 node less than pB,
        in the 2nd iteration pA go through 1 node more than pB,
        so they will meet at the intersection point
        **/
        
        return pA;
    }
};
