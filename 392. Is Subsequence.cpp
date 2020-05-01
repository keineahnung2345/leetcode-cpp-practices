//Greedy
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
            /*
            Greedy, unlike KMP, in which we need to fallback when encounted by a mismatch
            In this case, the matched characters can always be kept, no need to drop them in a mismatch
            In the example s = "abc", t = "ahbgdc", 
            when we know 'b' in s is different from 'h' in t, 
            we don't need to compare from 'a' in s again,
            we just move forward the index on t.
            */
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

//Greedy
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

//Follow-up, compare vector<string> ss(S1,S2,...Sk) with string t
//https://leetcode.com/problems/is-subsequence/discuss/87272/3-lines-C/92233
//O(len(t) * K)
class Solution {
public:
    bool isSubsequence(vector<string> ss, string t) {
        int n = ss.size();
        vector<int> cursors(n, 0);
        
        for(char c : t){
            //compare current char c in t with multiple strings in ss
            for(int i = 0; i < n; i++){
                cursors[i] += (ss[i][cursors[i]] == c);
            }
        }
        
        vector<int> ans(n);
        for(int i = 0; i < ss.size(); i++){
            ans[i] = (cursors[i] == ss[i].size());
        }
        
        return ans;
    }
};

//Follow-up, compare vector<string> ss(S1,S2,...Sk) with string t
//https://leetcode.com/problems/is-subsequence/discuss/87272/3-lines-C/92233
//skip redundant comparison
//O(len(t) + sum(len(s[i])))
class Solution {
public:
    bool isSubsequence(vector<string> ss, string t) {
        int n = ss.size();
        vector<int> cursors(n, 0);
        vector<vector<int>> waitingList(26);
        
        for(int i = 0; i < n; i++){
            /*
            for the char (ss[i][0]-'a'), 
            maintain the index of string in ss whose first char is that
            */
            waitingList[ss[i][0]-'a'].push_back(i);
        }
        
        for(char c : t){
            vector<int> old = waitingList[c-'a'];
            waitingList[c-'a'].clear();
            
            //only visit the string in ss who are waiting for c
            for(int i : old){
                //ss[i] matches, move its cursor forward
                cursors[i] += 1;
                //update waitingList concurrently
                waitingList[cursors[i]-'a'].push_back(i);
            }
        }
        
        vector<int> ans(n);
        for(int i = 0; i < ss.size(); i++){
            ans[i] = (cursors[i] == ss[i].size());
        }
        
        return ans;
    }
};
