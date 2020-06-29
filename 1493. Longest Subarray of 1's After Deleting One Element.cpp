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
