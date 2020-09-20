//Runtime: 20 ms, faster than 20.00% of C++ online submissions for Sum of All Odd Length Subarrays.
//Memory Usage: 8.5 MB, less than 40.00% of C++ online submissions for Sum of All Odd Length Subarrays.
class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        int n = arr.size();
        int ans = 0;
        
        for(int len = 1; len <= n; len += 2){
            for(int start = 0; start+len-1 < n; ++start){
                ans += accumulate(arr.begin()+start, arr.begin()+start+len, 0);
            }
        }
        
        return ans;
    }
};
