//sort
//https://www.geeksforgeeks.org/minimize-the-maximum-minimum-difference-after-one-removal-from-array/?ref=rp
//Runtime: 324 ms, faster than 33.33% of C++ online submissions for Minimum Difference Between Largest and Smallest Value in Three Moves.
//Memory Usage: 35.4 MB, less than 100.00% of C++ online submissions for Minimum Difference Between Largest and Smallest Value in Three Moves.
class Solution {
public:
    int minDifference(vector<int>& nums) {
        int n = nums.size();
        
        // cout << "n: " << n << endl;
        
        if(n <= 3) return 0;
        
        sort(nums.begin(), nums.end());
        
        int minDiff = INT_MAX;
        
        /*
        From the problem:
        Return the minimum difference between the largest and smallest value of nums after perfoming at most 3 moves.
        that means we can remove 3 elements,
        and following are the 4 ways of removing 3 elements
        */
        for(int i = 0; i <= 3; ++i){
            minDiff = min(minDiff, nums[n-1-i] - nums[3-i]);
        }
        
        // return min(nums[n-4] - nums[0], nums[n-1] - nums[3]);
        return minDiff;
    }
};

//partial_sort
//https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/discuss/730567/JavaC%2B%2BPython-Straight-Forward
//Runtime: 188 ms, faster than 100.00% of C++ online submissions for Minimum Difference Between Largest and Smallest Value in Three Moves.
//Memory Usage: 35.4 MB, less than 100.00% of C++ online submissions for Minimum Difference Between Largest and Smallest Value in Three Moves.
class Solution {
public:
    int minDifference(vector<int>& nums) {
        int n = nums.size();
        
        // cout << "n: " << n << endl;
        
        //after removing 3 elements, there will be at most one element
        if(n <= 4) return 0;
        
        /*
        looking at [nums.begin(), nums.end()),
        and make sure [nums.begin(), nums.begin()+4) is sorted
        */
        partial_sort(nums.begin(), nums.begin()+4, nums.end());
        /*
        looking at [nums.begin()+4, nums.end()),
        and make sure nth position has the right number,
        also elements before nth element are all <= nth element,
        and elements afater nth element are all >= nth element
        */
        nth_element(nums.begin()+4, nums.end()-4, nums.end());
        //now [nums.end()-4, nums.end()] are in right position
        
        //sort [nums.end()-4, nums.end()]
        sort(nums.end()-4, nums.end());
        
        int minDiff = INT_MAX;
        
        for(int i = 0; i <= 3; ++i){
            minDiff = min(minDiff, nums[n-1-i] - nums[3-i]);
        }
        
        return minDiff;
    }
};
