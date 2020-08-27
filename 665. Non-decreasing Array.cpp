//WA
//311 / 325 test cases passed.
//[3,4,2,3] should be false
class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int violate_count = 0;
        for(int i = 1; i < nums.size(); i++){
            if(nums[i] < nums[i-1]){
                violate_count++;
            }
        }
        // cout << violate_count << endl;
        return violate_count <= 1;
    }
};

//Approach #1: Brute Force
//time: O(N^2), space: O(1)
//Runtime: 128 ms, faster than 6.85% of C++ online submissions for Non-decreasing Array.
//Memory Usage: 27.2 MB, less than 12.55% of C++ online submissions for Non-decreasing Array.
class Solution {
public:
    bool monotone_increasing(vector<int>& nums){
        int n = nums.size();

        for(int i = 1; i < n; ++i){
            if(nums[i-1] > nums[i]){
                return false;
            }
        }

        return true;
    }

    bool checkPossibility(vector<int>& nums) {
        int n = nums.size();

        for(int i = 0; i < n; ++i){
            int old = nums[i];
            nums[i] = (i-1 >= 0) ? nums[i-1] : INT_MIN;
            if(monotone_increasing(nums)){
                return true;
            }
            nums[i] = old;
        }

        return false;
    }
};
