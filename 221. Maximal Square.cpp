//Approach #1 Brute Force [Accepted]
//Runtime: 24 ms, faster than 33.17% of C++ online submissions for Maximal Square.
//Memory Usage: 8.2 MB, less than 100.00% of C++ online submissions for Maximal Square.
//time: O((mn)^2), space: O(1)
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if(m == 0) return 0;
        int n = matrix[0].size();
        
        int maxslen = 0;
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(matrix[i][j] == '0') continue;
                int slen = 1;
                bool valid = true;
                while(slen + i < m && slen + j < n && valid){
                    for(int k = j; k <= j + slen; k++){
                        //i+slen: examine the (possible) last row of the square
                        if(matrix[i+slen][k] != '1'){
                            valid = false;
                            break;
                        }
                    }
                    for(int k = i; k <= i + slen; k++){
                        //j+slen: examine the (possible) last col of the square
                        if(matrix[k][j+slen] != '1'){
                            valid = false;
                            break;
                        }
                    }
                    if(valid){
                        slen++;
                    }
                }
                maxslen = max(maxslen, slen);
            }
        }
        
        return maxslen * maxslen;
    }
};

//Approach #2 (Dynamic Programming) [Accepted]
//Runtime: 24 ms, faster than 33.17% of C++ online submissions for Maximal Square.
//Memory Usage: 8.7 MB, less than 100.00% of C++ online submissions for Maximal Square.
//time: O(mn), space: O(mn)
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if(m == 0) return 0;
        int n = matrix[0].size();
        
        int maxslen = 0;
        vector<vector<int>> dp(m+1, vector(n+1, 0));
        
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(matrix[i-1][j-1] == '0') continue;
                //check top, left and top-left
                dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
                maxslen = max(maxslen, dp[i][j]);
            }
        }
        
        return maxslen * maxslen;
    }
};
