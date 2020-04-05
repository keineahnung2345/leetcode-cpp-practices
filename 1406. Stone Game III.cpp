//Recursion + memorization
//Runtime: 528 ms, faster than 33.33% of C++ online submissions for Stone Game III.
//Memory Usage: 146.5 MB, less than 100.00% of C++ online submissions for Stone Game III.
class Solution {
public:
    vector<int> memo;
    
    int maxScore(vector<int>& stoneValue, int n, int cur){
        if(cur >= n) return 0;
        
        // cout << "cur: " << cur << endl;
        if(memo[cur] != INT_MIN) return memo[cur];
        
        memo[cur] = max({stoneValue[cur]-maxScore(stoneValue, n, cur+1),
                       stoneValue[cur]+stoneValue[cur+1]-maxScore(stoneValue, n, cur+2),
                       stoneValue[cur]+stoneValue[cur+1]+stoneValue[cur+2]-maxScore(stoneValue, n, cur+3)});
        
        // cout << cur << " " << memo[cur] << endl;
        return memo[cur];
    };
    
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        memo = vector<int>(n, INT_MIN);
        stoneValue.push_back(0);
        stoneValue.push_back(0);
        int score = maxScore(stoneValue, n, 0);
        if(score == 0) return "Tie";
        if(score > 0) return "Alice";
        return "Bob";
    }
};

//DP
//https://leetcode.com/problems/stone-game-iii/discuss/564260/JavaC%2B%2BPython-DP-O(1)-Space
//Runtime: 468 ms, faster than 66.67% of C++ online submissions for Stone Game III.
//Memory Usage: 132.6 MB, less than 100.00% of C++ online submissions for Stone Game III.
//time: O(N^2), space: O(N)
class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int> dp(n, INT_MIN);
        
        for(int i = n-1; i >= 0; i--){
            for(int k = 0, take = 0; k <= 2 && i+k < n; k++){
                take += stoneValue[i+k];
                dp[i] = max(dp[i], take - ((i+k+1<n)?dp[i+k+1]:0));
            }
            // cout << i << " " << dp[i] << endl;
        }
        
        if(dp[0] > 0) return "Alice";
        if(dp[0] < 0) return "Bob";
        return "Tie";
    }
};

//DP, O(1) space
//https://leetcode.com/problems/stone-game-iii/discuss/564260/JavaC%2B%2BPython-DP-O(1)-Space
//Runtime: 492 ms, faster than 66.67% of C++ online submissions for Stone Game III.
//Memory Usage: 126.5 MB, less than 100.00% of C++ online submissions for Stone Game III.
//time: O(N^2), space: O(1)
class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        //we only need to remember dp[i+1],dp[i+2],dp[i+2] to update dp[i]
        vector<int> dp(4, INT_MIN);
        
        for(int i = n-1; i >= 0; i--){
            //initialization
            dp[i%4] = INT_MIN;
            for(int k = 0, take = 0; k <= 2 && i+k < n; k++){
                take += stoneValue[i+k];
                dp[i%4] = max(dp[i%4], take - ((i+k+1<n)?dp[(i+k+1)%4]:0));
            }
            // cout << i << " " << dp[i] << endl;
        }
        
        if(dp[0] > 0) return "Alice";
        if(dp[0] < 0) return "Bob";
        return "Tie";
    }
};
