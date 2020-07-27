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

//https://leetcode.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/discuss/743381/Python-6-lines-O(nlogm)-solution
//Runtime: 1056 ms, faster than 46.01% of C++ online submissions for Find a Value of a Mysterious Function Closest to Target.
//Memory Usage: 193.9 MB, less than 100.00% of C++ online submissions for Find a Value of a Mysterious Function Closest to Target.
//time: O(nlog(max(arr)))
class Solution {
public:
    int closestToTarget(vector<int>& arr, int target) {
        int n = arr.size();
        int ans = INT_MAX;
        /*
        at index j,
        it contains 
        arr[0] & ... & arr[j], 
        arr[1] & ... & arr[j], 
        ..., 
        arr[j-1] & arr[j], 
        arr[j]
        
        for these numbers,
        arr[j] is the largest, and it takes log(arr[j]) bits.
        If we look at bit representations,
        arr[j-1] & arr[j] unset some '1's from arr[j],
        and arr[j-2] & arr[j-1] & arr[j] unset more '1's in arr[j-1] & arr[j],
        ..., and so on, since we have at most log(arr[j]) ones in arr[j],
        so when we are at index j, the size of the set "sum" is O(log(arr[i]))
        
        for all ending index j, the size of "sum" is then O(log(max(arr)))
        */
        set<int> sums;
        
        for(int e : arr){
            set<int> tmp;
            transform(sums.begin(), sums.end(), inserter(tmp, tmp.end()), 
                      [&e](int sum){return (sum & e);});
            tmp.insert(e);
            swap(tmp, sums);
            for(int sum : sums){
                ans = min(ans, abs(sum - target));
            }
        }
        
        return ans;
    }
};
