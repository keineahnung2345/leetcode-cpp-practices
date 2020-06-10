//backtrack
//Runtime: 536 ms, faster than 19.94% of C++ online submissions for Beautiful Arrangement.
//Memory Usage: 6 MB, less than 71.95% of C++ online submissions for Beautiful Arrangement.
//time: O(#permutations), space: O(N)
class Solution {
public:
    int N;
    
    void backtrack(int& count, vector<int>& perm, vector<bool>& used){
        if(perm.size() == N){
            count++;
        }else{
            for(int i = 0; i < N; i++){
                //i+1: the value to be inserted
                //perm.size()+1: the value's index in perm(1-based)
                if(!used[i] && ((i+1) % (perm.size()+1) == 0 || (perm.size()+1) % (i+1) == 0)){
                    used[i] = true;
                    perm.push_back(i);
                    backtrack(count, perm, used);
                    used[i] = false;
                    perm.pop_back();
                }
            }
        }
    }
    
    int countArrangement(int N) {
        this->N = N;
        int count = 0;
        vector<int> perm;
        vector<bool> used(N, false);
        backtrack(count, perm, used);

        return count;
    }
};

//optimized backtracking
//Runtime: 360 ms, faster than 37.06% of C++ online submissions for Beautiful Arrangement.
//Memory Usage: 6.1 MB, less than 61.13% of C++ online submissions for Beautiful Arrangement.
class Solution {
public:
    int N;
    
    int backtrack(int cur, bitset<15>& used){
        if(cur > N){
            return 1;
        }else{
            int count = 0;
            
            for(int i = 0; i < N; i++){
                //i+1: the value to be inserted
                //cur: the value's index in perm(1-based)
                if(!used[i] && ((i+1) % cur == 0 || cur % (i+1) == 0)){
                    used[i] = 1;
                    count += backtrack(cur+1, used);
                    used[i] = 0;
                }
            }
            
            return count;
        }
    }
    
    int countArrangement(int N) {
        this->N = N;
        bitset<15> used;
        return backtrack(1, used);
    }
};

//recursion with memorization
//Runtime: 88 ms, faster than 72.42% of C++ online submissions for Beautiful Arrangement.
//Memory Usage: 9.3 MB, less than 20.58% of C++ online submissions for Beautiful Arrangement.
class Solution {
public:
    int N;
    map<pair<int, int>, int> memo;
    
    int backtrack(int cur, bitset<15>& used){
        pair<int, int> key = make_pair(cur, used.to_ulong());
        
        if(cur > N){
            return 1;
        }else if(memo.find(key) != memo.end()){
            return memo[key];
        }else{
            for(int i = 0; i < N; i++){
                //i+1: the value to be inserted
                //cur: the value's index in perm(1-based)
                if(!used[i] && ((i+1) % cur == 0 || cur % (i+1) == 0)){
                    used[i] = 1;
                    memo[key] += backtrack(cur+1, used);
                    used[i] = 0;
                }
            }
            
            return memo[key];
        }
    }
    
    int countArrangement(int N) {
        this->N = N;
        bitset<15> used;
        return backtrack(1, used);
    }
};

//top-down DP/recursion with memorization
//Runtime: 16 ms, faster than 88.26% of C++ online submissions for Beautiful Arrangement.
//Memory Usage: 11.6 MB, less than 19.82% of C++ online submissions for Beautiful Arrangement.
class Solution {
public:
    int N;
    vector<vector<int>> dp;
    
    int backtrack(int cur, bitset<15>& used){
        int kused = used.to_ulong();
        if(cur > N){
            return 1;
        }else if(dp[cur][kused] != -1){
            return dp[cur][kused];
        }else{
            dp[cur][kused] = 0;
            
            for(int i = 0; i < N; i++){
                //i+1: the value to be inserted
                //cur: the value's index in perm(1-based)
                if(!used[i] && ((i+1) % cur == 0 || cur % (i+1) == 0)){
                    used[i] = 1;
                    dp[cur][kused] += backtrack(cur+1, used);
                    used[i] = 0;
                }
            }
            // cout << "(" << cur << ", " << kused << "): " << dp[cur][kused] << endl;
            return dp[cur][kused];
        }
    }
    
    int countArrangement(int N) {
        this->N = N;
        bitset<15> used;
        dp = vector<vector<int>>(N+1, vector<int>(1<<N, -1));
        backtrack(1, used);
        return dp[1][0];
    }
};
