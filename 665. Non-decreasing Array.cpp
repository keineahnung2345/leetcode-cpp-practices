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

//Approach #2: Reduce to Smaller Problem
//time: O(N), start and end look an element at most once, and the remaining length of subarray is at most 4
//space: O(1), the length of subarray passed to brute_force is at most 4
//Runtime: 60 ms, faster than 81.80% of C++ online submissions for Non-decreasing Array.
//Memory Usage: 27.2 MB, less than 16.47% of C++ online submissions for Non-decreasing Array.
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

    bool brute_force(vector<int> nums) {
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

    bool checkPossibility(vector<int>& nums) {
        int n = nums.size();

        int start = 0, end = n-1;

        while(start+2 < n && nums[start] <= nums[start+1] && nums[start+1] <= nums[start+2]){
            ++start;
        }

        //remove duplicate checking by "end-2 >= 0" -> "end-2 >= start"
        while(end-2 >= start && nums[end-2] <= nums[end-1] && nums[end-1] <= nums[end]){
            --end;
        }

        int len = end-start+1;
        // cout << start << ", " << end << ", " << len << endl;
        if(len <= 2){
            /*
            the while loop continues when the length of subarray >= 3, 
            so if it exit with length <= 2, 
            it means that there are no wrong elements
            */
            return true;
        }else if(len >= 5){
            /*
            consider [1,3,2,4,2],
            start and end will be 0 and 4,
            we need to revise one element in nums[0...2] and
            another element in nums[2...4],
            so it's invalid
            */
            return false;
        }

        return brute_force(vector<int>(nums.begin()+start, nums.begin()+start+len));
    }
};
