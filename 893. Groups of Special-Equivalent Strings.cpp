/**
You are given an array A of strings.

Two strings S and T are special-equivalent if after any number of moves, S == T.

A move consists of choosing two indices i and j with i % 2 == j % 2, and swapping S[i] with S[j].

Now, a group of special-equivalent strings from A is a non-empty subset S of A such that any string not in S is not special-equivalent with any string in S.

Return the number of groups of special-equivalent strings from A.

 

Example 1:

Input: ["a","b","c","a","c","c"]
Output: 3
Explanation: 3 groups ["a","a"], ["b"], ["c","c","c"]
Example 2:

Input: ["aa","bb","ab","ba"]
Output: 4
Explanation: 4 groups ["aa"], ["bb"], ["ab"], ["ba"]
Example 3:

Input: ["abc","acb","bac","bca","cab","cba"]
Output: 3
Explanation: 3 groups ["abc","cba"], ["acb","bca"], ["bac","cab"]
Example 4:

Input: ["abcd","cdab","adcb","cbad"]
Output: 1
Explanation: 1 group ["abcd","cdab","adcb","cbad"]
 

Note:

1 <= A.length <= 1000
1 <= A[i].length <= 20
All A[i] have the same length.
All A[i] consist of only lowercase letters.
**/

//Runtime: 8 ms, faster than 73.97% of C++ online submissions for Groups of Special-Equivalent Strings.
class Solution {
public:
    int numSpecialEquivGroups(vector<string>& A) {
        if(A.size()==0) return 0;
        
        vector<string> B;
        
        for(int i = 0; i < A.size(); i++){
            string s;
            
            for(int j = 0; j < A[i].size(); j+=2){
                s.push_back(A[i][j]);
            }
            for(int j = 1; j < A[i].size(); j+=2){
                s.push_back(A[i][j]);
            }
            sort(s.begin(), s.begin()+(s.size()+1)/2);
            sort(s.begin()+(s.size()+1)/2, s.end());
            B.push_back(s);
        }
        sort(B.begin(), B.end());
        
        int groups = 1;
        for(int i = 1; i < B.size(); i++){
            if(B[i]!=B[i-1]) groups++;
        }
        return groups;
    }
};

/**
Approach 1: Counting
Intuition and Algorithm

Let's try to characterize a special-equivalent string S, by finding a function C so that S≡T⟺C(S)=C(T).

Through swapping, we can permute the even indexed letters, and the odd indexed letters. 
What characterizes these permutations is the count of the letters: 
all such permutations have the same count, and different counts have different permutations.

Thus, the function C(S)= (the count of the even indexed letters in S, 
followed by the count of the odd indexed letters in S) 
successfully characterizes the equivalence relation.

Afterwards, we count the number of unique C(S) for S∈A.

//Java
class Solution {
    public int numSpecialEquivGroups(String[] A) {
        Set<String> seen = new HashSet();
        for (String S: A) {
            int[] count = new int[52];
            for (int i = 0; i < S.length(); ++i)
                count[S.charAt(i) - 'a' + 26 * (i % 2)]++;
            seen.add(Arrays.toString(count));
        }
        return seen.size();
    }
}

Complexity Analysis

Time Complexity: O(∑_i(A_i).length)

Space Complexity: O(N), where N is the length of A. 
**/
