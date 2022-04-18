# 713. Subarray Product Less Than K

[leetcode - 713. Subarray Product Less Than K](https://leetcode.com/problems/subarray-product-less-than-k/)

## Naive
//TLE
//75 / 84 test cases passed.
//time: O(N^2), space: O(1)
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;
        
        for(int i = 0; i < n; ++i){
            long long product = 1LL;
            int j;
            for(j = i; j < n; ++j){
                product *= nums[j];
                if(product >= k) break;
            }
            //[i...j-1]
            // cout << i << "..." << j-1 << endl;
            ans += (j-i);
        }
        
        return ans;
    }
};

## Approach #1: Binary Search on Logarithms

Runtime: 312 ms, faster than 30.64% of C++ online submissions for Subarray Product Less Than K.
    
Memory Usage: 100.5 MB, less than 6.14% of C++ online submissions for Subarray Product Less Than K.

about epsilon: https://stackoverflow.com/a/253874/10651567

time: O(NlogN), space: O(N)

```cpp
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if(k == 0) return 0;
        int n = nums.size();
        double logk = log(k);
        
        // cout << "logk: " << logk << endl;
        
        vector<double> psum(n+1, 0);
        
        // cout << psum[0] << " ";
        for(int i = 1; i <= n; ++i){
            //psum[i]: lognums[0...i-1]
            psum[i] = psum[i-1] + log((double)nums[i-1]);
            // cout << psum[i] << " ";
        }
        // cout << endl;
        
        // cout << std::numeric_limits<double>::epsilon() << endl;
        // cout << max(*max_element(psum.begin(), psum.end()), logk) * numeric_limits<double>::epsilon() << endl;
        
        int ans = 0;
        
        for(int i = 0; i < n; ++i){
            /*
            binary search for j s.t.
            nums[i...j] < k and is largest,
            i.e. lognums[i...j] < logk and is largest,
            lognums[i...j] = psum[j+1]-psum[i]
            */
            int left = i, right = n-1;
            int mid;
            
            //find right boundary
            while(left <= right){
                mid = (left+right)>>1;
                // cout << left << ", " << mid << ", " << right << endl;
                if(psum[mid+1] >= psum[i] + logk - max(psum[mid+1], psum[i] + logk)*std::numeric_limits<double>::epsilon()){
                    right = mid-1;
                    //right is always valid
                }else{
                    left = mid+1;
                    //left becomes invalid
                }
            }
            
            // cout << "[" << i << ", " << right << "]" << endl;
            ans += (right - i + 1);
        }
        
        return ans;
    }
};
```


## Approach #2: Sliding Window [Accepted]

Runtime: 236 ms, faster than 98.00% of C++ online submissions for Subarray Product Less Than K.

Memory Usage: 92.2 MB, less than 9.99% of C++ online submissions for Subarray Product Less Than K.

time: O(N), space: O(1)

```cpp
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int n = nums.size();
        
        int left = 0, right = 0;
        long long prod = 1LL;
        int ans = 0;
        
        for(int right = 0; right < n; ++right){
            prod *= nums[right];
            
            while(left < n && prod >= k){
                prod /= nums[left];
                ++left;
            }
            
            // cout << "[" << left << ", " << right << "]: " << prod << endl;
            
            if(left <= right) ans += (right-left+1);
        }
        
        return ans;
    }
};
```
