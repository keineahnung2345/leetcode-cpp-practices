//Runtime: 160 ms, faster than 16.92% of C++ online submissions for Remove Duplicates from Sorted Array.
//Memory Usage: 10 MB, less than 99.23% of C++ online submissions for Remove Duplicates from Sorted Array.

/**
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        int last = nums[0];
        int i = 1;
        while(i < nums.size()){
            if(nums[i] == last){
                nums.erase(nums.begin()+i);
            }else{
                last = nums[i];
                i++;
            }
        }
        return nums.size();
    }
};
**/

/**
Approach 1: Two Pointers
slow pointer points to the last unique number,
it will be compared with the element fast pointer points to
**/

/**
time: O(n)
space: O(1)
**/

//Runtime: 24 ms, faster than 99.10% of C++ online submissions for Remove Duplicates from Sorted Array.
//Memory Usage: 9.9 MB, less than 99.34% of C++ online submissions for Remove Duplicates from Sorted Array.

/**
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        int slow = 0;
        for(int fast = 1; fast < nums.size(); fast++){
            if(nums[fast] != nums[slow]){
                slow++;
                nums[slow] = nums[fast];
            }
            // for(int i = 0; i < nums.size(); i++){
            //     cout << nums[i] << " ";
            // }
            // cout << endl;
        }
        return slow+1;
    }
};
**/
