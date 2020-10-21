//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Largest Substring Between Two Equal Characters.
//Memory Usage: 6.5 MB, less than 81.12% of C++ online submissions for Largest Substring Between Two Equal Characters.
class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s) {
        int n = s.size();
        
        vector<int> first(26, n), last(26, -1);
        
        for(int i = 0; i < n; ++i){
            if(first[s[i]-'a'] == n) first[s[i]-'a'] = i;
            last[s[i]-'a'] = i;
        }
        
        int ans = -1;
        
        for(int i = 0; i < 26; ++i){
            ans = max(ans, last[i]-first[i]-1);
        }
        
        return ans;
    }
};
