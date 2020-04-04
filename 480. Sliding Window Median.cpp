//Runtime: 324 ms, faster than 6.78% of C++ online submissions for Sliding Window Median.
//Memory Usage: 10 MB, less than 100.00% of C++ online submissions for Sliding Window Median.
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int l = 0;
        vector<int> window(k);
        vector<double> ans;
        
        while(l+k-1 < nums.size()){
            //update the data structure
            if(l == 0){
                window.assign(nums.begin()+l, nums.begin()+l+k);
                sort(window.begin(), window.end());
            }else{
                window.erase(find(window.begin(), window.end(), nums[l-1]));
                //insert the new element into right place
                //lower_bound: position of smallest element >= x
                auto it = lower_bound(window.begin(), window.end(), nums[l+k-1]);
                window.insert(it, nums[l+k-1]);
            }
            
            int median;
            if(k % 2 == 1){
                ans.push_back(window[k/2]);
            }else{
                double median = 0.0;
                //to avoid overflow
                median += window[k/2-1]/2.0;
                median += window[k/2]/2.0;
                ans.push_back(median);
            }
            
            l++;
        }
        
        return ans;
    }
};
