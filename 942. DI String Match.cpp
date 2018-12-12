/**
Given a string S that only contains "I" (increase) or "D" (decrease), let N = S.length.

Return any permutation A of [0, 1, ..., N] such that for all i = 0, ..., N-1:

If S[i] == "I", then A[i] < A[i+1]
If S[i] == "D", then A[i] > A[i+1]
 

Example 1:

Input: "IDID"
Output: [0,4,1,3,2]
Example 2:

Input: "III"
Output: [0,1,2,3]
Example 3:

Input: "DDI"
Output: [3,2,0,1]
 

Note:

1 <= S.length <= 10000
S only contains characters "I" or "D".
**/

/**
Approach 1: Greedy
Intuition

If we see say S[0] == 'I', we can always put 0 as the first element; similarly, if we see S[0] == 'D', we can always put N as the first element.

Say we have a match for the rest of the string S[1], S[2], ... using N distinct elements. Notice it doesn't matter what the elements are, only that they are distinct and totally ordered. Then, putting 0 or N at the first character will match, and the rest of the elements (1, 2, ..., N or 0, 1, ..., N-1) can use the matching we have.

Algorithm

Keep track of the smallest and largest element we haven't placed. If we see an 'I', place the small element; otherwise place the large element.

Complexity Analysis

Time Complexity: O(N), where N is the length of S.

Space Complexity: O(N). 

**/
//Your runtime beats 55.92 % of cpp submissions.
class Solution {
public:
    vector<int> diStringMatch(string S) {
        vector<int> ans;
        
        int low = 0;
        int high = S.size();
        
        for(int i = 0; i < S.size(); i++){
            if(S[i]=='I')
                ans.push_back(low++);
            else
                ans.push_back(high--);
        }
        // ans.push_back(high); 
        ans.push_back(low);
        return ans;
    }
};

