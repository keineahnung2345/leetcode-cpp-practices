//Approach #1 Brute Force
//TLE
//32 / 555 test cases passed.
//time: O(N^2), space: O(1)
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int ans = 0;
        
        for(int start = 0; start < nums.size(); start++){
            int zeros = 0, ones = 0;
            for(int end = start; end < nums.size(); end++){
                if(nums[end] == 0){
                    zeros++;
                }else{
                    ones++;
                }
                if(zeros == ones){
                    ans = max(ans, end-start+1);
                }
            }
        }
        
        return ans;
    }
};

//Approach #2 Using Extra Array [Accepted]
//Runtime: 96 ms, faster than 90.38% of C++ online submissions for Contiguous Array.
//Memory Usage: 20 MB, less than 41.67% of C++ online submissions for Contiguous Array.
//time: O(N), space: O(N)
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        vector<int> arr(2*nums.size()+1, -2);
        
        arr[nums.size()] = -1;
        int ans = 0, count = 0;
        
        for(int i = 0; i < nums.size(); i++){
            count += (nums[i] == 0 ? -1 : 1);
            if(arr[count + nums.size()] >= -1){
                ans = max(ans, i-arr[count+nums.size()]);
            }else{
                arr[count+nums.size()] = i;
            }
        }
        
        return ans;
    }
};
