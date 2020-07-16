//TLE
//91 / 92 test cases passed.
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> dp(n, INT_MAX);
        
        dp[0] = 0;
        
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j <= min(n-1, i+nums[i]); ++j){
                //we can jump from i to j
                dp[j] = min(dp[j], dp[i]+1);
            }
        }
        
        return dp[n-1];
    }
};

//monotonic deque
//https://leetcode.com/problems/jump-game-ii/discuss/230778/C%2B%2B-deque-based-beats-99
//Runtime: 20 ms, faster than 87.98% of C++ online submissions for Jump Game II.
//Memory Usage: 13.6 MB, less than 18.24% of C++ online submissions for Jump Game II.
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        
        if(n <= 1) return 0;
        
        /*
        pair: (steps required to jump to i, farthest position reachable from i)
        later element requires more steps, but it can reach farther position
        */
        deque<pair<int, int>> dq;
        
        dq.push_back({0, nums[0]});
        
        for(int i = 1; i < n; ++i){
            while(!dq.empty() && dq.front().second < i){
                //cannot reach current position
                dq.pop_front();
            }
            
            if(i+nums[i] > dq.back().second){
                /*
                if the farthest position(p) can be reached from i is
                same as j(j < i),
                then we can discard i,
                that's because the steps required by j 
                to reach p is definitely <= 
                the steps required by i
                */
                dq.push_back({dq.front().first+1, i+nums[i]});
            }
        }
        
        //dq.front() has minimum steps required to reach n-1
        return dq.front().first+1;
    }
};

//bfs
//Runtime: 32 ms, faster than 23.31% of C++ online submissions for Jump Game II.
//Memory Usage: 13.2 MB, less than 88.44% of C++ online submissions for Jump Game II.
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int start = 0, end = 0, jump = 0;
        
        //while we cannot reach n-1
        while(end < n-1){
            // cout << "jump: " << jump << ", [" << start << ", " << end << "]" << endl;
            int nextend = end;
            
            //calculate the farthest position we can jump from current range
            for(int i = start; i <= min(end, n-1); ++i){
                // cout << "i: " << i << ", " << i + nums[i] << endl;
                nextend = max(nextend, i + nums[i]);
            }
            
            //assume we just jump one position from last end
            start = end+1;
            end = nextend;
            ++jump;
            // cout << "jump: " << jump << ", [" << start << ", " << end << "]" << endl;
        }
        
        return jump;
    }
};
