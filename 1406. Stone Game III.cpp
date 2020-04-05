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
