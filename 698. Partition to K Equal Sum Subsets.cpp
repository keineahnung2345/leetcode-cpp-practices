//dfs
//TLE
//64 / 149 test cases passed.
class Solution {
public:
    int partitionSum;
    vector<int> subsets;
    bool ans;
    
    void backtrack(vector<int>& nums, int k, int start){
        if(start == nums.size()){
            for(int val : subsets){
                cout << val << " ";
            }
            cout << endl;
            ans = all_of(subsets.begin(), subsets.end(), 
                          [this](const int& val){return val == partitionSum;});
        }else if(!ans){ //early stop
            for(int i = 0; i < k; i++){
                //early stop
                if(subsets[i] + nums[start] > partitionSum)
                    continue;
                subsets[i] += nums[start];
                backtrack(nums, k, start+1);
                subsets[i] -= nums[start];
            }
        }
    };
    
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        subsets = vector<int>(k, 0);
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum % k != 0) return false;
        partitionSum = sum/k;
        ans = false;
        backtrack(nums, k, 0);
        return ans;
    }
};

//dfs, add some tricks to speed up
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Partition to K Equal Sum Subsets.
//Memory Usage: 9.4 MB, less than 40.17% of C++ online submissions for Partition to K Equal Sum Subsets.
//time: O(k^(N-k)*k!)
//space: O(N)
class Solution {
public:
    int partitionSum;
    vector<int> subsets;
    bool ans;
    
    void backtrack(vector<int>& nums, int k, int start){
        if(start == nums.size()){
            ans = all_of(subsets.begin(), subsets.end(), 
                          [this](const int& val){return val == partitionSum;});
        }else if(!ans){ //early stop
            for(int i = 0; i < k; i++){
                //early stop
                if(subsets[i] + nums[start] > partitionSum)
                    continue;
                subsets[i] += nums[start];
                backtrack(nums, k, start+1);
                subsets[i] -= nums[start];
                /*
                https://leetcode.com/problems/partition-to-k-equal-sum-subsets/solution/
                speed up: TLE -> 584ms
                if nums[start] does not fit an empty group,
                (subsets[i] == 0 means an empty group),
                it doesn't fit the following other empty groups too
                when subsets[i] == 0, subsets[i+1] will always be 0
                */
                if(subsets[i] == 0) break;
            }
        }
    };
    
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum % k != 0) return false;
        partitionSum = sum/k;
        ans = false;
        /*
        speed up: 584ms -> 4ms
        start to build subset from larger elements first,
        so that the smaller subset can be considered earlier
        */
        sort(nums.rbegin(), nums.rend());
        //speed up (0th element is the largest)
        if(nums[0] > partitionSum) return false;
        //speed up : remove the elements just equal to partitionSum
        //the two speed up above: 4ms -> 0ms
        int start = 0;
        while(start < nums.size() && 
              nums[start] == partitionSum){
            start++;
            k--;
        }
        subsets = vector<int>(k, 0);
        backtrack(nums, k, start);
        return ans;
    }
};

//dp + bitmask
//https://leetcode.com/problems/partition-to-k-equal-sum-subsets/discuss/480707/C%2B%2B-DP-bit-manipulation-in-20-lines
//Runtime: 88 ms, faster than 26.04% of C++ online submissions for Partition to K Equal Sum Subsets.
//Memory Usage: 17.4 MB, less than 12.91% of C++ online submissions for Partition to K Equal Sum Subsets.
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int n = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum % k != 0) return false;
        int partitionSum = sum/k;
        
        //len(nums) <= 16, so there are 2^16 states
        vector<int> dp(1<<n, -1);
        dp[0] = 0;
        
        //each mask represents a state
        for(int mask = 0; mask < (1 << n); mask++){
            //skip invalid state
            if(dp[mask] == -1) continue;
            //try to add nums[i] into the state
            for(int i = 0; i < n; i++){
                /*
                dp[mask]: (sum of all subsets) % partitionSum
                dp[mask] + nums[i] <= partitionSum: we must choose a number
                that can be fit into a subset
                */
                if(!(mask & (1<<i)) && dp[mask] + nums[i] <= partitionSum){
                    /*
                    we set the dp value as xxx % partitionSum,
                    so that next time we can choose a number that can fit
                    in a subset by checking 
                    dp[mask] + nums[i] <= partitionSum
                    */
                    dp[mask | (1<<i)] = (dp[mask] + nums[i]) % partitionSum;
                }
            }
        }
        
        //it's importatnt to add () around 1<<i !!
        //'-' 's precedence is higher than '<<' !!
        return dp[(1<<n) - 1] == 0;
    }
};
