//TLE
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if(p.size() > s.size()) return vector<int>();
        vector<int> ans;
        
        sort(p.begin(), p.end());
        
        for(int i = 0; i < s.size() - (p.size()-1); i++){
            string s1 = s.substr(i, p.size());
            sort(s1.begin(), s1.end());
            if(s1 == p) ans.push_back(i);
        }
        
        return ans;
    }
};

//https://leetcode.com/problems/find-all-anagrams-in-a-string/discuss/92007/Sliding-Window-algorithm-template-to-solve-all-the-Leetcode-substring-search-problem.
//sort by votes, dico's answer(7 votes)
//Runtime: 52 ms, faster than 31.03% of C++ online submissions for Find All Anagrams in a String.
//Memory Usage: 10.3 MB, less than 96.82% of C++ online submissions for Find All Anagrams in a String.
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> ans;
        map<char, int> pcount;
        for(char c: p){
            if(pcount.find(c) == pcount.end()){
                pcount[c] = 1;
            }else{
                pcount[c]++;
            }
        }
        
        map<char, int> wcount; //the occurence of chars in a sliding window
        int start = 0, end = 0, match = 0;
        
        while(end < s.size()){
            char c1 = s[end];
            if(pcount.find(c1) != pcount.end()){
                //update wcount
                if(wcount.find(c1) == wcount.end()){
                    wcount[c1] = 1;
                }else{
                    wcount[c1]++;
                }
                //increase 'match' when the occurences match each other
                if(pcount[c1] == wcount[c1])match++;
            }
            
            //find start while 'match' is the correct number
            while(match == pcount.size()){
                //only when the matched kind of char's count are right,
                // and the total matched count are right,
                // we find an valid start
                if(end - start + 1 == p.size()){
                    ans.push_back(start);
                }
                
                //discard s[start], update sliding window and 'match'
                char c2 = s[start];
                if(pcount.find(c2) != pcount.end()){
                    wcount[c2]--;
                    if(wcount[c2] < pcount[c2])match--;
                }
                start++;
            }
        
            end++;
        }
        
        return ans;
    }
};
