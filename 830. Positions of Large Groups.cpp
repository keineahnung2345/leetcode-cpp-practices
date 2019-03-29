/**
In a string S of lowercase letters, these letters form consecutive groups of the same character.

For example, a string like S = "abbxxxxzyy" has the groups "a", "bb", "xxxx", "z" and "yy".

Call a group large if it has 3 or more characters.  We would like the starting and ending positions of every large group.

The final answer should be in lexicographic order.

 

Example 1:

Input: "abbxxxxzzy"
Output: [[3,6]]
Explanation: "xxxx" is the single large group with starting  3 and ending positions 6.
Example 2:

Input: "abc"
Output: []
Explanation: We have "a","b" and "c" but no large group.
Example 3:

Input: "abcdddeeeeaabbbcd"
Output: [[3,5],[6,9],[12,14]]
 

Note:  1 <= S.length <= 1000
**/

//Runtime: 8 ms, faster than 100.00% of C++ online submissions for Positions of Large Groups.
//Memory Usage: 9.1 MB, less than 100.00% of C++ online submissions for Positions of Large Groups.

class Solution {
public:
    vector<vector<int>> largeGroupPositions(string S) {
        int start = 0, end = 0;
        char c = '\0';
        vector<vector<int>> ans;
        
        for(int i = 0; i < S.size(); i++){
            if(S[i] != c){
                //last group
                if(end - start >= 2){
                    //length > 3 group
                    ans.push_back(vector<int> {start, end});
                }
                //update for current group
                c = S[i];
                start = i;
                end = i;
            }else{
                end = i;
            }
            // cout << c << " " << start << " " << end << endl;
        }
        
        if(end - start >= 2){
            //length > 3 group
            ans.push_back(vector<int> {start, end});
        }
        
        return ans;
    }
};

/**
Approach #1: Two Pointer [Accepted]
Intuition

We scan through the string to identify the start and end of each group. If the size of the group is at least 3, we add it to the answer.

Algorithm

Maintain pointers i, j with i <= j. The i pointer will represent the start of the current group, and we will increment j forward until it reaches the end of the group.

We know that we have reached the end of the group when j is at the end of the string, or S[j] != S[j+1]. At this point, we have some group [i, j]; and after, we will update i = j+1, the start of the next group.
**/

/**
Complexity Analysis

Time Complexity: O(N)O(N), where NN is the length of S.

Space Complexity: O(N)O(N), the space used by the answer.
**/

//Runtime: 8 ms, faster than 100.00% of C++ online submissions for Positions of Large Groups.
//Memory Usage: 9.3 MB, less than 100.00% of C++ online submissions for Positions of Large Groups.
/**
class Solution {
public:
    vector<vector<int>> largeGroupPositions(string S) {
        int start = 0, end = 0;
        vector<vector<int>> ans;
        
        for(int end = 0; end < S.size(); end++){
            //check for a group when the string ends
            if(end == S.size()-1 || S[end] != S[end+1]){
                //deal with old group
                if(end-start+1 >= 3){
                    ans.push_back(vector<int> {start, end});
                }
                //update for new group
                start = end+1;
            }
        }
        
        return ans;
    }
};
**/

