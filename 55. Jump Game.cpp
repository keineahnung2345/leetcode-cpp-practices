//TLE
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int N = nums.size();
        vector<bool> dp(N, false);
        
        dp[N-1] = true;
        for(int i = N-1; i >= 0; i--){
            if(nums[i] >= 1){
                //can reach to one of dp[i+j] which is true
                for(int j = 1; j <= nums[i] && i+j < N; j++){
                    if(dp[i+j]){
                        dp[i] = true;
                        break;
                    }
                }
            }
        }
        
        
        for(int i = 0; i < N; i++){
            if(nums[i] >= 1){
                //can reach to one of dp[i+j] which is true
                for(int j = 1; j <= nums[i] && i-j >= 0; j++){
                    if(dp[i-j]){
                        dp[i] = true;
                        break;
                    }
                }
            }
        }
        
        return dp[0];
    }
};

//TLE
//74 / 75 test cases passed.
//Graph
class Solution {
public:
    bool canJump(vector<int>& nums) {
        map<int, vector<int>> graph;
        int n = nums.size();
        
        for(int i = 0; i < n; i++){
            // for(int j = max(0, i-nums[i]); j <= min(n-1, i+nums[i]); j++){
            for(int j = i; j <= min(n-1, i+nums[i]); j++){
                graph[i].push_back(j);
            }
        }
        
        queue<int> q;
        q.push(0);
        
        vector<bool> visited(n, false);
        visited[0] = true;
        
        while(!q.empty()){
            int cur = q.front(); q.pop();
            
            for(int next : graph[cur]){
                if(!visited[next]){
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
        
        return visited[n-1];
    }
};

//Approach 1: Backtracking
//TLE
//time: O(2^n), space: O(n)
class Solution {
public:
    bool canJumpFromPos(vector<int>& nums, int pos){
        int N = nums.size();
        if(pos == N-1) return true;
        
        int furthestJump = min(pos+nums[pos], N-1);
        // for(int nextPos = pos+1; nextPos <= furthestJump; nextPos++){
        for(int nextPos = furthestJump; nextPos > pos; nextPos--){
            if(canJumpFromPos(nums, nextPos)){
                return true;
            }
        }
        
        return false;
    };
    
    bool canJump(vector<int>& nums) {
        return canJumpFromPos(nums, 0);
    }
};

//Approach 2: Dynamic Programming Top-down(backtracking with memorization)
//TLE
//time: O(n^2), space: O(n)

class Solution {
public:
    enum Index {
        GOOD, BAD, UNKNOWN
    };
    
    vector<Index> memo;
    
    bool canJumpFromPos(vector<int>& nums, int pos){
        int N = nums.size();
        if(memo[pos] != Index::UNKNOWN){
            return memo[pos] == GOOD ? true : false;
        }
        
        int furthestJump = min(pos+nums[pos], N-1);
        // for(int nextPos = pos+1; nextPos <= furthestJump; nextPos++){
        for(int nextPos = furthestJump; nextPos > pos; nextPos--){
            if(canJumpFromPos(nums, nextPos)){
                memo[pos] = Index::GOOD;
                return true;
            }
        }
        
        memo[pos] = Index::BAD;
        return false;
    };
    
    bool canJump(vector<int>& nums) {
        int N = nums.size();
        memo = vector<Index>(N);
        for(int i = 0; i < N-1; i++){
            memo[i] = Index::UNKNOWN;
        }
        memo[N-1] = Index::GOOD;
        
        return canJumpFromPos(nums, 0);
    }
};

//Approach 3: Dynamic Programming Bottom-up
//Runtime: 516 ms, faster than 14.01% of C++ online submissions for Jump Game.
//Memory Usage: 9.1 MB, less than 100.00% of C++ online submissions for Jump Game.
//time: O(n^2), space: O(n)

class Solution {
public:
    enum Index {
        GOOD, BAD, UNKNOWN
    };
    
    vector<Index> memo;
    
    bool canJump(vector<int>& nums) {
        int N = nums.size();
        memo = vector<Index>(N);
        for(int i = 0; i < N-1; i++){
            memo[i] = Index::UNKNOWN;
        }
        memo[N-1] = Index::GOOD;
        
        for(int pos = N-2; pos >= 0; pos--){
            int furthestJump = min(pos+nums[pos], N-1);
            for(int nextPos = furthestJump; nextPos > pos; nextPos--){
                if(memo[nextPos] == Index::GOOD){
                    memo[pos] = Index::GOOD;
                    break;
                }
            }
        }
        
        return memo[0] == Index::GOOD;
    }
};

//Approach 4: Greedy
//Runtime: 12 ms, faster than 73.33% of C++ online submissions for Jump Game.
//Memory Usage: 9.3 MB, less than 100.00% of C++ online submissions for Jump Game.
//time: O(n), space: O(1)

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int N = nums.size();
        int lastGood = N-1;
        
        for(int i = N-2; i >= 0; i--){
            if(i + nums[i] >= lastGood){
                lastGood = i;
            }
        }
        
        return lastGood == 0;
    }
};
