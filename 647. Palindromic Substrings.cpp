//Runtime: 24 ms, faster than 32.32% of C++ online submissions for Palindromic Substrings.
//Memory Usage: 21.9 MB, less than 12.00% of C++ online submissions for Palindromic Substrings.
class Solution {
public:
    int countSubstrings(string s) {
        int N = s.size();
        vector<vector<int>> dp(N, vector<int>(N, 0));
        int ans = 0;
        
        //width 1
        //each char is a palindrome itself
        for(int i = 0; i < N; i++){
            dp[i][i] = 1;
            ans++;
        }
        
        for(int width = 2; width <= N; width++){
            for(int start = 0; start + width -1 < N; start++){
                int end = start + width -1;
                //if its substring is not valid, then it's not valid
                if(start+1 <= end-1 && !dp[start+1][end-1]){
                    dp[start][end] = false;
                    continue;
                }
                dp[start][end] = (s[start] == s[end]);
                if(dp[start][end]){
                    // cout << start << " " << end << endl;
                    ans++;
                }
            }
        }
        
        return ans;
    }
};
