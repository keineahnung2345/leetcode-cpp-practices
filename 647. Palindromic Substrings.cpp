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

//DP, O(N) space
//Runtime: 12 ms, faster than 60.81% of C++ online submissions for Palindromic Substrings.
//Memory Usage: 6.4 MB, less than 100.00% of C++ online submissions for Palindromic Substrings.
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        vector<int> dp(n+2, 0);
        int ans = 0;
        
        for(int l = n; l >= 1; l--){
            //note taht we have changed the r to reverse order!
            for(int r = n; r >= l; r--){
                /*
                dp[r-1] is dp[l+1][r-1] in previous method,
                so we want dp[r-1] to be updated after dp[r],
                so that dp[r-1] means dp[l+1][r-1], not dp[l][r-1]
                */
                if((l+1 >= r-1 || dp[r-1] != 0) && s[l-1] == s[r-1]){
                    dp[r] = 1;
                    ans += dp[r];
                }else{
                    dp[r] = 0;
                }
            }
        }
        
        return ans;
    }
};

//center expansion
//https://leetcode.com/problems/palindromic-substrings/discuss/105687/Python-Straightforward-with-Explanation-(Bonus-O(N)-solution)
//O(N^2)
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        int ans = 0;
        
        //center could be n char of s and also n-1 spaces between chars
        for(int center = 0; center < 2*n-1; center++){
            //center = 0(0th char) -> left: 0, right: 0
            //center = 1(btw 0th and 1st char) -> left: 0, right: 1
            //center = 5(btw 2nd and 3rd char) -> left: 2, right: 3
            int left = center/2;
            int right = center/2 + center%2;
            
            while(left >= 0 && right < n && s[left] == s[right]){
                ans++;
                left--;
                right++;
            }
        }
        
        return ans;
    }
};
