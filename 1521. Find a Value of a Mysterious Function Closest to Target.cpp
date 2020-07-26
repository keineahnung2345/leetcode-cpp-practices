//https://leetcode.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/discuss/743146/Java-Straightforward-O(N2)-with-optimization
//Runtime: 272 ms, faster than 94.55% of C++ online submissions for Find a Value of a Mysterious Function Closest to Target.
//Memory Usage: 61.7 MB, less than 100.00% of C++ online submissions for Find a Value of a Mysterious Function Closest to Target.
//time: O(N^2), space: O(1)
class Solution {
public:
    int closestToTarget(vector<int>& arr, int target) {
        int n = arr.size();
        int res = INT_MAX;
        
        for(int i = 0; i < n; ++i){
            int sum = arr[i];
            for(int j = i; j < n; ++j){
                sum &= arr[j];
                res = min(res, abs(sum-target));
                if(res == 0) return res;
                if(sum < target){
                    /*
                    in inner loop, 
                    the more operations we do,
                    the smaller the "sum",
                    so if sum is already smaller than target,
                    we can just skip further operations
                    */
                    break;
                }
            }
            
            if(sum > target){
                /*
                if sum > target, 
                than sum must be arr[i] & ... & arr[n-1]
                (it completes the inner loop)
                
                in outer loop,
                when we increase i,
                we will get larger "sum",
                so we can just skip further calculation of "sum"
                */
                break;
            }
        }
        
        return res;
    }
};
