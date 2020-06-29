//Runtime: 92 ms, faster than 88.93% of C++ online submissions for Longest Subarray of 1's After Deleting One Element.
//Memory Usage: 36.7 MB, less than 25.00% of C++ online submissions for Longest Subarray of 1's After Deleting One Element.
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int slow = 0, fast = 0;
        int ans = 0;
        int n = nums.size();
        int last0 = -1;
        
        while(fast < n){
            while(slow < n && nums[slow] == 0) ++slow;
            if(slow == n) break;
            fast = max(slow, fast);
            int os = slow, of = fast;
            
            if(nums[fast] == 1){
                //last0 >= slow: whether cross a 0
                ans = max(ans, fast - slow + 1 - (last0 >= slow));
                ++fast;
            }else if(last0 < slow){
                //cout << "cross0" << endl;
                last0 = fast;
                ++fast;
            }else{
                //cout << "new window" << endl;
                slow = last0+1;
                //nums[fast] is 0
                fast = fast-1;
            }
            //cout << "[" << os << ", " << of << "]: " << ans << endl;
        }
        
        //if all 1, we must remove a 1
        return (ans == n) ? ans-1 : ans;
    }
};

//sliding window
//https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/discuss/708112/JavaC%2B%2BPython-Sliding-Window-at-most-one-0
//Runtime: 132 ms, faster than 52.03% of C++ online submissions for Longest Subarray of 1's After Deleting One Element.
//Memory Usage: 36.7 MB, less than 25.00% of C++ online submissions for Longest Subarray of 1's After Deleting One Element.
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int k = 1, ans = 0;
        for(int slow = 0, fast = 0; fast < nums.size(); ++fast){
            /*
            by including nums[fast] to our window,
            we use one quota of 0,
            so now we allow k-1 more 0s to be added
            */
            if(nums[fast] == 0) --k;
            
            /*
            k must be >=0,
            so we shrink our window to 
            make the condition hold
            */
            while(k < 0){
                if(nums[slow] == 0){
                    ++k;
                }
                ++slow;
            }
            
            /*
            length-1 of longest subarray
            */
            ans = max(ans, fast - slow + 1 - 1);
        }
        
        return ans;
    }
};
