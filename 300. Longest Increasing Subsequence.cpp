//DP
//Runtime: 80 ms, faster than 27.26% of C++ online submissions for Longest Increasing Subsequence.
//Memory Usage: 7.9 MB, less than 100.00% of C++ online submissions for Longest Increasing Subsequence.
//time: O(N^2), space: O(N)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        
        vector<int> dp(n, 1);
        int ans = 1;
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < i; j++){
                if(nums[i] > nums[j]){
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
            // cout << dp[i] << " ";
            ans = max(ans, dp[i]);
        }
        // cout << endl;
        
        return ans;
    }
};

//DP + binary search
//Runtime: 4 ms, faster than 89.41% of C++ online submissions for Longest Increasing Subsequence.
//Memory Usage: 7.9 MB, less than 100.00% of C++ online submissions for Longest Increasing Subsequence.
//https://algorithmsandme.com/longest-increasing-subsequence-in-onlogn/
//https://github.com/keineahnung2345/fucking-algorithm/blob/note/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E7%B3%BB%E5%88%97/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E8%AE%BE%E8%AE%A1%EF%BC%9A%E6%9C%80%E9%95%BF%E9%80%92%E5%A2%9E%E5%AD%90%E5%BA%8F%E5%88%97.md
//time: O(NlogN), space: O(N)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        
        vector<int> top;
        
        for(int poker : nums){
            int left = 0, right = top.size()-1;
            while(left <= right){
                int mid = left + (right-left)/2;
                if(poker < top[mid]){
                    right = mid - 1;
                }else if(poker == top[mid]){
                    right = mid - 1;
                }else if(poker > top[mid]){
                    left = mid+1;
                }
            }
            
            if(left == top.size()){
                //poker is larger than all cards in top
                top.push_back(poker);
            }else{
                //overlay current poker to the specific pile
                top[left] = poker;
            }
            
        }
        
        return top.size();
    }
};

//Approach 1: Brute Force, Recursion
//TLE
//21 / 24 test cases passed.
//time: O(2^N), because for each element, there are 2 cases: taken or nottaken
class Solution {
public:
    int lengthOfLIS(vector<int>& nums, int prev = -1, int cur = 0) {
        /*
        nums[cur] is the element we consider to append,
        it cannot be out of the range of nums
        */
        if(cur == nums.size()) return 0;
        int taken = 0;
        //we may append current element into sequence
        /*
        initial state: prev is -1, and cur = 0,
        that means we are considering the 0th element,
        and the 0th element is always ok to be appended to the empty sequence
        */
        if(prev < 0 || nums[cur] > nums[prev]){
            taken = 1 + lengthOfLIS(nums, cur, cur+1);
        }
        //skip current element
        int nottaken = lengthOfLIS(nums, prev, cur+1);
        // cout << prev << ", " << cur << " : " << taken << ", " << nottaken << endl;
        return max(taken, nottaken);
    }
};

//Approach 2: Recursion with Memoization
//Runtime: 748 ms, faster than 5.13% of C++ online submissions for Longest Increasing Subsequence.
//Memory Usage: 110.3 MB, less than 6.25% of C++ online submissions for Longest Increasing Subsequence.
//time: O(N^2), space: O(N^2)
class Solution {
public:
    vector<vector<int>> memo;
    
    int lengthOfLIS(vector<int>& nums, int prev, int cur) {
        /*
        nums[cur] is the element we consider to append,
        it cannot be out of the range of nums
        */
        if(cur == nums.size()) return 0;
        if(memo[prev+1][cur] != -1) return memo[prev+1][cur];
        int taken = 0;
        //we may append current element into sequence
        /*
        initial state: prev is -1, and cur = 0,
        that means we are considering the 0th element,
        and the 0th element is always ok to be appended to the empty sequence
        */
        if(prev < 0 || nums[cur] > nums[prev]){
            taken = 1 + lengthOfLIS(nums, cur, cur+1);
        }
        //skip current element
        int nottaken = lengthOfLIS(nums, prev, cur+1);
        // cout << prev << ", " << cur << " : " << taken << ", " << nottaken << endl;
        memo[prev+1][cur] = max(taken, nottaken);
        return memo[prev+1][cur];
    }
    
    int lengthOfLIS(vector<int>& nums){
        /*
        padding ahead,
        because prev may be -1
        */
        int n = nums.size();
        memo = vector<vector<int>>(n+1, vector(n, -1));
        return lengthOfLIS(nums, -1, 0);
    }
};
