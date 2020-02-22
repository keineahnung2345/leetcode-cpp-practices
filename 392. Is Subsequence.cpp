//Runtime: 60 ms, faster than 87.38% of C++ online submissions for Is Subsequence.
//Memory Usage: 17.1 MB, less than 66.67% of C++ online submissions for Is Subsequence.
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int si = 0, ti = 0;
        while(si < s.size() && ti < t.size()){
            for(; ti < t.size() && s[si] != t[ti]; ti++){
                // cout << s[si] << " " << t[ti] << endl;
            }
            
            if(s[si] == t[ti]){
                //s[si] and t[ti] match, both seq go ahead
                si++; //only if s[si] matches, we can go ahead in seq "s"
                ti++;
            }
        }
        
        //check if we look through s
        return si == s.size();
    }
};

//https://leetcode.com/problems/is-subsequence/discuss/87272/3-lines-C
class Solution {
public:
    bool isSubsequence(string s, string t) {
        string::iterator si = s.begin();
        for(char c : t){
            si += (c == *si);
        }
        return si == s.end();
    }
};
