//DP, O(N^2) space
//Runtime: 28 ms, faster than 53.48% of C++ online submissions for Delete Operation for Two Strings.
//Memory Usage: 12 MB, less than 55.56% of C++ online submissions for Delete Operation for Two Strings.
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        
        vector<vector<int>> dp(m+1, vector(n+1, 0));
        
        for(int i = 0; i <= m; i++){
            for(int j = 0; j <= n; j++){
                if(i == 0 && j == 0){
                    dp[i][j] = 0;
                }else if(i == 0){
                    dp[i][j] = j;
                }else if(j == 0){
                    dp[i][j] = i;
                }else if(word1[i-1] == word2[j-1]){
                    dp[i][j] = dp[i-1][j-1];
                }else{
                    dp[i][j] = min(
                        dp[i-1][j], //remove word1[i-1]
                        dp[i][j-1] //remove word2[j-1]
                    ) + 1;
                }
            }
        }
        
        return dp[m][n];
    }
};

//DP, O(N) space
//Runtime: 20 ms, faster than 73.66% of C++ online submissions for Delete Operation for Two Strings.
//Memory Usage: 6.7 MB, less than 100.00% of C++ online submissions for Delete Operation for Two Strings.
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        
        vector<int> dp(n+1, 0);
        
        int dp_is1_js1;
        
        for(int i = 0; i <= m; i++){
            for(int j = 0; j <= n; j++){
                int tmp = dp[j];
                if(i == 0 || j == 0){
                    dp[j] = i+j;
                }else if(word1[i-1] == word2[j-1]){
                    dp[j] = dp_is1_js1;
                }else{
                    dp[j] = min(
                        dp[j], //remove word1[i-1]
                        dp[j-1] //remove word2[j-1]
                    ) + 1;
                }
                dp_is1_js1 = tmp;
            }
        }
        
        return dp[n];
    }
};

//Approach #3 Using Longest Common Subsequence- Dynamic Programming [Accepted]
//https://leetcode.com/articles/delete-operation-for-two-strings/
//time: O(m*n), space: O(m*n)
class Solution {
public:
    int LCS(string word1, string word2){
        int m = word1.size();
        int n = word2.size();
        
        vector<vector<int>> dp(m+1, vector(n+1, 0));
        
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(word1[i-1] == word2[j-1]){
                    dp[i][j] = dp[i-1][j-1] + 1;
                }else{
                    dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
                }
            }
        }
        
        return dp[m][n];
    };
    
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        
        return m + n - 2 * LCS(word1, word2);
    }
};
