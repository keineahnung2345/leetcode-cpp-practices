//Runtime: 168 ms, faster than 16.18% of C++ online submissions for Minimum Number of Steps to Make Two Strings Anagram.
//Memory Usage: 18.3 MB, less than 100.00% of C++ online submissions for Minimum Number of Steps to Make Two Strings Anagram.

class Solution {
public:
    int minSteps(string s, string t) {
        map<char, int> scount, tcount;
        int ans = 0;
        
        for(char c : s){
            scount[c]++;
        }
        
        for(char c : t){
            tcount[c]++;
        }
        
        for(auto it = tcount.begin(); it != tcount.end(); it++){
            //focus on the count of char needed to changed to
            if(scount.find(it->first) == scount.end()){
                ans += it->second;
            }else{
                ans += max(it->second - scount[it->first], 0);
            }
        }
        
        return ans;
    }
};
