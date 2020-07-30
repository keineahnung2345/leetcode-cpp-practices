//DP
//Runtime: 28 ms, faster than 48.19% of C++ online submissions for Word Break.
//Memory Usage: 10.8 MB, less than 61.87% of C++ online submissions for Word Break.
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n+1, false);
        //padding, assume empty string is a valid dictionary word
        dp[n] = true;
        
        for(int i = n-1; i >= 0; --i){
            dp[i] = find(wordDict.begin(), wordDict.end(), s.substr(i)) != wordDict.end();
            
            // split s into s[i:j-1] and s[j:]
            for(int j = n; j >= i+1; --j){
                //s[j:] is composed by valid dictionary words
                //and s[i:j-1] is a valid dictionary word
                dp[i] = dp[j] && find(wordDict.begin(), wordDict.end(), s.substr(i, j-i)) != wordDict.end();
                if(dp[i]) break;
            }
        }
        
        return dp[0];
    }
};
