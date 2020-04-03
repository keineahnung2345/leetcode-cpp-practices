//Runtime: 56 ms, faster than 79.54% of C++ online submissions for Sliding Window Maximum.
//Memory Usage: 10.7 MB, less than 100.00% of C++ online submissions for Sliding Window Maximum.
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int curMax = INT_MAX, curMaxPos = -1;
        vector<int> ans;
        for(int i = 0; i+k-1 < nums.size(); i++){
            //[i, i+k-1] : sliding window's range
            if(nums[i+k-1] >= curMax){
                /*
                set curMax's initial value as INT_MAX, 
                so that in first iteration it will go to 
                the "else if(i > curMaxPos)" part
                */
                curMax = nums[i+k-1];
                curMaxPos = i+k-1;
            }else if(i > curMaxPos){
                /*
                set curMaxPos's intial value as -1,
                so that in first iteration it will come here
                */
                auto it = max_element(nums.begin()+i, nums.begin()+i+k);
                curMax = *it;
                curMaxPos = it - nums.begin();
            }
            ans.push_back(curMax);
        }
        
        return ans;
    }
};
