//TLE
//62 / 69 test cases passed.
class Solution {
public:
    int maxNonOverlapping(vector<int>& nums, int target) {
        int n = nums.size();
        
        vector<int> accsum = nums;
        
        // cout << accsum[0] << " ";
        for(int i = 1; i < n; ++i){
            accsum[i] += accsum[i-1];
            // cout << accsum[i] << " ";
        }
        // cout << endl;
        
        int cursum = 0;
        vector<int>::iterator it;
        vector<pair<int, int>> dp(n); //(count, end)
        int ans = 0;
        
        for(int i = 0; i < n; ++i){
            cursum = (i > 0) ? accsum[i-1] : 0;
            // cout << "i: " << i << endl;
            // cout << "cursum: " << cursum << endl;
            // cout << "finding " << cursum + target << endl;
            if((it = find(accsum.begin()+i, accsum.end(), cursum+target)) != 
               accsum.end()){
                int curend = it - accsum.begin();
                // cout << "accsum[" << curend << "]: " << accsum[curend] << endl;
                
                dp[i] = {1, curend};
                for(int j = 0; j < i; ++j){
                    if(dp[j].second < i && dp[j].first >= 1){
                        //no overlap
                        dp[i] = {dp[j].first+1, curend};
                    }
                }
                
                // cout << "[" << i << ", " << dp[i].second << "]: " << dp[i].first << endl; //"\t";
                ans = max(ans, dp[i].first);
            }
        }
        // cout << endl;
        
        return ans;
    }
};

//improved from above, using unordered_map
//TLE
//66 / 69 test cases passed.
class Solution {
public:
    int maxNonOverlapping(vector<int>& nums, int target) {
        int n = nums.size();
        
        vector<int> accsum = nums;
        unordered_map<int, vector<int>> accsum2idx;
        
        // cout << accsum[0] << " ";
        accsum2idx[accsum[0]].push_back(0);
        for(int i = 1; i < n; ++i){
            accsum[i] += accsum[i-1];
            accsum2idx[accsum[i]].push_back(i);
            // cout << accsum[i] << " ";
        }
        // cout << endl;
        
        int cursum = 0;
        vector<int>::iterator it;
        vector<pair<int, int>> dp(n); //(count, end)
        int ans = 0;
        
        for(int i = 0; i < n; ++i){
            cursum = (i > 0) ? accsum[i-1] : 0;
            // cout << "i: " << i << endl;
            // cout << "cursum: " << cursum << endl;
            // cout << "finding " << cursum + target << endl;
            // if((it = find(accsum.begin()+i, accsum.end(), cursum+target)) != 
            //    accsum.end()){
            
            while(!accsum2idx[cursum+target].empty() && accsum2idx[cursum+target].front() < i){
                accsum2idx[cursum+target].erase(accsum2idx[cursum+target].begin());
            }
            if(!accsum2idx[cursum+target].empty()){
                int curend = accsum2idx[cursum+target].front();
                // int curend = it - accsum.begin();
                // cout << "accsum[" << curend << "]: " << accsum[curend] << endl;
                
                dp[i] = {1, curend};
                for(int j = i-1; j >= 0; --j){
                    if(dp[j].second < i && dp[j].first >= 1){
                        //no overlap
                        dp[i] = {dp[j].first+1, curend};
                        break;
                    }
                }
                
                // cout << "[" << i << ", " << dp[i].second << "]: " << dp[i].first << endl; //"\t";
                ans = max(ans, dp[i].first);
            }
        }
        // cout << endl;
        
        return ans;
    }
};

//greedy, hashmap
//https://leetcode.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/discuss/780887/Java-Detailed-Explanation-DPMapPrefix-O(N)
//Runtime: 400 ms, faster than 100.00% of C++ online submissions for Maximum Number of Non-Overlapping Subarrays With Sum Equals Target.
//Memory Usage: 82.9 MB, less than 50.00% of C++ online submissions for Maximum Number of Non-Overlapping Subarrays With Sum Equals Target.
class Solution {
public:
    int maxNonOverlapping(vector<int>& nums, int target) {
        int n = nums.size();
        /*
        unordered_map's search/insertion/deletion time: 
        average O(1), worst O(n)
        */
        unordered_map<int, int> sum2count;
        int sum = 0;
        int count = 0;
        
        /*
        if we can find a i s.t. nums[0...i] = target,
        count should be sum2count[0]+1 = 1
        */
        sum2count[0] = 0;
        
        for(int i = 0; i < n; ++i){
            //sum: accumulate sum of nums[0...i]
            sum += nums[i];
            
            if(sum2count.find(sum-target) != sum2count.end()){
                /*
                we can find a j s.t. nums[0...j] + target = nums[0...i],
                so nums[j+1...i] sums to target
                */
                //choose btw original count and current found count
                count = max(count, sum2count[sum-target] + 1);
            }
            
            sum2count[sum] = count;
        }
        
        return count;
    }
};

