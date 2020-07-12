//dfs + memorization
//Runtime: 128 ms, faster than 60.00% of C++ online submissions for Stone Game IV.
//Memory Usage: 12.3 MB, less than 100.00% of C++ online submissions for Stone Game IV.
class Solution {
public:
    vector<int> memo;
    
    bool dfs(int n){
        // cout << "n: " << n << endl;
        if(memo[n] != -1){
            return memo[n];
        }
        
        for(int i = 1; i * i <= n; ++i){
            if(!dfs(n - i*i)){
                return memo[n] = true;
            }
        }
        
        return memo[n] = false;
    };
    
    bool winnerSquareGame(int n) {
        memo = vector<int>(n+1, -1);
        
        memo[0] = 0;
        for(int i = 1; i*i <= n; ++i){
            memo[i*i] = 1;
        }
        
        return dfs(n);
    }
};
