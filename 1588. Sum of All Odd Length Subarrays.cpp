//Runtime: 20 ms, faster than 20.00% of C++ online submissions for Sum of All Odd Length Subarrays.
//Memory Usage: 8.5 MB, less than 40.00% of C++ online submissions for Sum of All Odd Length Subarrays.
//time: O(N^3)
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

//https://leetcode.com/problems/sum-of-all-odd-length-subarrays/discuss/854184/JavaC%2B%2BPython-O(N)-Time-O(1)-Space
//Runtime: 4 ms, faster than 89.52% of C++ online submissions for Sum of All Odd Length Subarrays.
//Memory Usage: 8.3 MB, less than 90.10% of C++ online submissions for Sum of All Odd Length Subarrays.
//time: O(N), space: O(1)
class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        int n = arr.size();
        int ans = 0;
        
        for(int i = 0; i < n; ++i){
            //i+1: count of subarrays starting at [0...i]
            //n-i: count of subarrays ending at [i...n-1]
            //(i+1)*(n-i): number of subarrays containing i
            /*
            in the subarrays containing i, 
            there are odd-length ones and even-length ones,
            and it's obvious that either:
            1. number of odd-length ones = number of even-length ones
            2. number of odd-length ones = number of even-length ones+1,
            so number of odd-length ones = ((i+1)*(n-i)+1)/2
            */
            ans += ((i+1)*(n-i)+1)/2*arr[i];
        }
        
        return ans;
    }
};
