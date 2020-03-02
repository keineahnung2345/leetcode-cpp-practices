//Approach 1: Dynamic Programming
//time: O(N^2), space: O(N^2)
//Runtime: 12 ms, faster than 50.14% of C++ online submissions for Stone Game.
//Memory Usage: 16.4 MB, less than 20.00% of C++ online submissions for Stone Game.

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int N = piles.size();
        
        vector<vector<int>> dp(N, vector<int>(N));
        
        for(int size = 1; size <= N; size++){
            for(int i = 0; i+size-1 < N; i++){
                int j = i+size-1;
                //already take N-size stones, remain size stones
                // cout << i << ", " << j << endl;
                int parity = (N-size)%2 == 0;
                
                //boundary
                int r = (i+1 < N) ? dp[i+1][j] : 0;
                int l = (j-1 >= 0) ? dp[i][j-1] : 0;
                //alex's turn
                if(parity == 1){
                    dp[i][j] = max(piles[i]+r,
                        piles[j]+l);
                }else{
                    dp[i][j] = min(-piles[i]+r, 
                        -piles[j]+l);
                }
            }
        }
        
        return dp[0][N-1] > 0;
    }
};

//Approach 2: Mathematical
//time: O(1)
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Stone Game.
//Memory Usage: 7.9 MB, less than 100.00% of C++ online submissions for Stone Game.
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        return true;
    }
};
