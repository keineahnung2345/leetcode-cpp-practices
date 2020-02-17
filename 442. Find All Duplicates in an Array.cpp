//use extra space
//Runtime: 224 ms, faster than 5.24% of C++ online submissions for Find All Duplicates in an Array.
//Memory Usage: 27.9 MB, less than 5.00% of C++ online submissions for Find All Duplicates in an Array.

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        map<int, int> count;
        vector<int> ans;
        for(int num : nums){
            if(count.find(num) == count.end()){
                count[num] = 1;
            }else{
                count[num]++;
                ans.push_back(num);
            }
        }
        return ans;
    }
};

//https://leetcode.com/problems/find-all-duplicates-in-an-array/discuss/92395/C%2B%2B-beats-98
//without extra space, O(N)
//Runtime: 112 ms, faster than 89.64% of C++ online submissions for Find All Duplicates in an Array.
//Memory Usage: 14.9 MB, less than 90.00% of C++ online submissions for Find All Duplicates in an Array.

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> ans;
        for(int _num : nums){
            //1<=num<=nums.size(), so this is always valid
            //use the array itself to record whether "num" has occurred
            //nums[j] may be negative because there could exist i where i < j && nums[i]-1 == abs(nums[j])
            //so here we revert it to its original value
            int num = abs(_num);
            nums[num-1] *= -1;
            if(nums[num-1] > 0){
                ans.push_back(num);
            }
        }
        return ans;
    }
};
