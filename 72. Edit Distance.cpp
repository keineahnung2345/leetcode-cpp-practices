//DP
//Runtime: 32 ms, faster than 17.80% of C++ online submissions for Edit Distance.
//Memory Usage: 8.9 MB, less than 87.50% of C++ online submissions for Edit Distance.
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        
        /*
        different from other problem,
        here dp[0][?] and dp[?][0] are meaningful.
        They represents the situation when word1 is "" and when word2 is ""
        */
        vector<vector<int>> dp(m+1, vector(n+1, 0));
        
        for(int i = 0; i <= m; i++){
            for(int j = 0; j <= n; j++){
                if(i == 0 && j == 0){
                    dp[i][j] = 0;
                }else if(j == 0){
                    /*
                    word1: [0, i-1] //i 's upper limit is m
                    word2: ""
                    
                    this means we need to delete i char from word1
                    */
                    dp[i][j] = i;
                }else if(i == 0){
                    /*
                    word1: ""
                    word2: [0, j-1] //j 's upper limit is n
                    */
                    dp[i][j] = j;
                }else if(word1[i-1] == word2[j-1]){
                    //no op
                    dp[i][j] = dp[i-1][j-1];
                }else{
                    dp[i][j] = min({
                        //remove word1[i-1]
                        dp[i-1][j],
                        //insert word2[j-1]
                        dp[i][j-1],
                        //replace word1[i-1] to word2[j-1]
                        dp[i-1][j-1]
                        }) + 1;
                }
            }
        }
        
        return dp[m][n];
    }
};

//DP, O(1) space
//https://leetcode.com/problems/edit-distance/discuss/25846/C%2B%2B-O(n)-space-DP
//Runtime: 16 ms, faster than 61.68% of C++ online submissions for Edit Distance.
//Memory Usage: 6.3 MB, less than 100.00% of C++ online submissions for Edit Distance.
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
                if(i == 0 && j == 0){
                    dp[j] = 0;
                }else if(j == 0){
                    /*
                    word1: [0, i-1] //i 's upper limit is m
                    word2: ""
                    
                    this means we need to delete i char from word1
                    */
                    dp[j] = i;
                }else if(i == 0){
                    /*
                    word1: ""
                    word2: [0, j-1] //j 's upper limit is n
                    */
                    dp[j] = j;
                }else if(word1[i-1] == word2[j-1]){
                    //no op
                    dp[j] = dp_is1_js1;
                }else{
                    dp[j] = min({
                        //remove word1[i-1]
                        //dp[i-1][j]
                        dp[j],
                        //insert word2[j-1]
                        //dp[i][j-1]
                        dp[j-1],
                        //replace word1[i-1] to word2[j-1]
                        //dp[i-1][j-1]
                        dp_is1_js1
                        }) + 1;
                }
                dp_is1_js1 = tmp;
            }
        }
        
        return dp[n];
    }
};
