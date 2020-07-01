//Runtime: 380 ms, faster than 55.92% of C++ online submissions for Number of Subsequences That Satisfy the Given Sum Condition.
//Memory Usage: 47.7 MB, less than 100.00% of C++ online submissions for Number of Subsequences That Satisfy the Given Sum Condition.
class Solution {
public:
    int MOD = 1e9+7;
    
    long long int power(long long int x, long long int y){
        long long int res = 1;

        // Update x if it is more than or equal to p
        x = x % MOD;

        while(y > 0){
            // If y is odd, multiply x with result
            if(y & 1){
                //don't need mod multiply for now?
                // res = multiply(res,x) % MOD;
                res = (res*x) % MOD;
            }

            // y must be even now
            y >>= 1;
            // x = multiply(x, x) % MOD;
            x = (x*x) % MOD;
        }

        return res;
    };
    
    int numSubseq(vector<int>& nums, int target) {
        int n = nums.size();
        int count = 0;
        
        sort(nums.begin(), nums.end());
        
        // for(int& num : nums){
        //     cout << num << " ";
        // }
        // cout << endl;
        
        /*
        target is large enough,
        so even the subarray: [nums.back()] is acceptable.
        */
        if(target >= 2*nums.back()){
            return power(2, n)-1;
        }
        
        for(int left = 0, right = n-1; left <= right; ++left){
            // cout << "left: " << left << endl;
            // discard too large elements
            while(right >= 0 && nums[left] + nums[right] > target){
                --right;
            }
            
            if(left <= right && nums[left] + nums[right] <= target){
                // cout << "[" << left << ", " << right << "]: " << power(2, right-left) << endl;
                /*
                for the subarray nums[left...right],
                keep nums[left] in the subarray,
                and for nums[left+1...right], 
                we can choose keep it or not
                so we can have totally 2^(right-left)
                combinations, 
                in which right-left is subarray's size-1
                */
                count = (count+ power(2, right-left))%MOD;
            }
        }
        
        return count;
    }
};

//Two Sum
//https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/discuss/709227/JavaC%2B%2BPython-Two-Sum
//Runtime: 340 ms, faster than 86.87% of C++ online submissions for Number of Subsequences That Satisfy the Given Sum Condition.
//Memory Usage: 50.1 MB, less than 100.00% of C++ online submissions for Number of Subsequences That Satisfy the Given Sum Condition.
//time: O(NlogN), space: O(N) or O(1)
class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        int n = nums.size();
        int MOD = 1e9+7;
        int ans = 0;
        vector<int> power(n, 1);
        
        //precalculate the powers
        for(int i = 1; i < n; ++i){
            power[i] = (power[i-1] << 1) % MOD;
        }
        
        sort(nums.begin(), nums.end());
        
        for(int l = 0, r = n-1; l <= r; ){
            if(nums[l] + nums[r] > target){
                //either decrease r or increase l
                --r;
            }else{
                ans = (ans + power[r-l]) % MOD;
                //either decrease r or increase l
                ++l;
            }
        }
        
        return ans;
    }
};
