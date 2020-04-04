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

//C++ multiset and middle iterator
//https://leetcode.com/problems/sliding-window-median/discuss/96340/O(n-log-k)-C%2B%2B-using-multiset-and-updating-middle-iterator
//Runtime: 80 ms, faster than 46.39% of C++ online submissions for Sliding Window Median.
//Memory Usage: 12.8 MB, less than 100.00% of C++ online submissions for Sliding Window Median.
//time: O(Nlogk)
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        multiset<int> window(nums.begin(), nums.begin()+k);
        /*
        if k is odd, midIt points to the median
        if k is even, we average *midIt and *prev(midIt)
        */
        auto midIt = next(window.begin(), k/2);
        vector<double> ans;
        int l = 0;
        
        while(l+k-1 < nums.size()){
            //window is initialized, so we don't update window when l == 0
            if(l > 0){
                //l+k-1 is now inside the window
                //insert nums[l+k-1]
                window.insert(nums[l+k-1]);
                if (nums[l+k-1] < *midIt){
                    //move the iterator to correct position
                    midIt--;
                }

                //l-1 is now outside the window
                //erase nums[l-1]
                if (nums[l-1] <= *midIt){
                    midIt++;
                }
                window.erase(window.lower_bound(nums[l-1]));
            }
            
            //to avoid overflow
            ans.push_back(*midIt/2.0 + *prev(midIt, 1 - k%2)/2.0);
            
            l++;
        }
        
        return ans;
    }
};
