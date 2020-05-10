//binary search
//https://leetcode.com/problems/split-array-largest-sum/discuss/89817/Clear-Explanation%3A-8ms-Binary-Search-Java
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Split Array Largest Sum.
//Memory Usage: 7.1 MB, less than 100.00% of C++ online submissions for Split Array Largest Sum.
class Solution {
public:
    bool isValid(vector<int>& nums, int m, long long maxSubSum){
        long long subSum = 0;
        int count = 1; //number of subarrays
        
        for(int num : nums){
            subSum += num;
            if(subSum > maxSubSum){
                /*
                current sub array's sum > maxSubSum,
                so we need a new split
                */
                subSum = num;
                count++;
                if(count > m){
                    return false;
                }
            }
        }
        
        return true;
    };
    
    int splitArray(vector<int>& nums, int m) {
        //the max value and sum of the array
        long long _max = 0, _sum = 0;
        
        for(long long num : nums){
            _max = max(_max, num);
            _sum += num;
        }
        
        /*
        suppose nums's length is n,
        if we can have n subarrays, the max value of sum of each subarray is _max
        if we can only have 1 subarray, the sum of this subarray is _sum
        */
        long long left = _max, right = _sum, mid;
        
        //[left, right]: inclusive
        while(left <= right){
            mid = left + (right-left)/2;
            // cout << left << ", " << mid << ", " << right << endl;
            if(isValid(nums, m, mid)){
                //mid is already searched, so next time we don't search mid
                //[left, mid) -> [left, mid-1]
                right = mid - 1;
            }else{
                //(mid, right] -> [mid+1, right]
                left = mid + 1;
            }
        }
        
        return (int)left;
    }
};
