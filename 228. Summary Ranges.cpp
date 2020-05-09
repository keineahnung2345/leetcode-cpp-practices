//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Summary Ranges.
//Memory Usage: 7 MB, less than 100.00% of C++ online submissions for Summary Ranges.
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return vector<string>();
        int start = nums[0], end = start;
        vector<string> ans;
        for(int i = 1; i < n; i++){
            // if(nums[i] - end == 1){
            if(end != INT_MAX && nums[i] == end+1){ //avoid overflow
                //extend old range
                end = nums[i];
            }else{
                //new range
                if(start == end)
                    ans.push_back(to_string(start));
                else
                    ans.push_back(to_string(start) + "->" + to_string(end));
                start = end = nums[i];
            }
        }
        
        //handle the last interval and when n is equal to 1
        if(start == end)
            ans.push_back(to_string(start));
        else
            ans.push_back(to_string(start) + "->" + to_string(end));
        
        return ans;
    }
};
