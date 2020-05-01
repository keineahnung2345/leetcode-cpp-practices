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

//DP
//Runtime: 24 ms, faster than 40.82% of C++ online submissions for Palindromic Substrings.
//Memory Usage: 20.4 MB, less than 12.00% of C++ online submissions for Palindromic Substrings.
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        /*
        padding 0 and n+1,
        used for dp[l+1][r-1]
        */
        vector<vector<int>> dp(n+2, vector<int>(n+2, 0));
        int ans = 0;
        
        //valid range is [1...n]
        for(int l = n; l >= 1; l--){
            for(int r = l; r <= n; r++){
                /*
                l and r is 1-based, 
                need to convert them to 0-based to index s
                */
                /*
                l+1 >= r-1 : s[l+1...r-1] will always be palindrome
                */
                if((l+1 >= r-1 || dp[l+1][r-1] != 0) && s[l-1] == s[r-1]){
                    dp[l][r] = 1; //dp[l+1][r-1]+1;
                    // cout << l << ", " << r << ", " << dp[l][r] << endl;
                    ans += dp[l][r];
                }else{
                    dp[l][r] = 0;
                }
            }
        }
        
        return ans;
    }
};
