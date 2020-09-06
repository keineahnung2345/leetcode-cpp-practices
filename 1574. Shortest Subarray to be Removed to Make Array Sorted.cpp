//Two pointer
//https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/discuss/830416/Java-Increasing-From-Left-Right-and-Merge-O(n)
//Runtime: 276 ms, faster than 100.00% of C++ online submissions for Shortest Subarray to be Removed to Make Array Sorted.
//Memory Usage: 66.9 MB, less than 75.00% of C++ online submissions for Shortest Subarray to be Removed to Make Array Sorted.
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size();
        
        int l = 0, r = n-1;
        
        while(l+1 < n && arr[l] <= arr[l+1]){
            ++l;
        }
        //arr[0...l] is non-decreasing
        
        //the whole array is non-decreasing
        if(l == n-1) return 0;
        
        while(r-1 > 0 && arr[r-1] <= arr[r]){
            --r;
        }
        //arr[r...n-1] is non-decreasing
        
        //remove [l+1...n-1] or [0...r-1]
        int min_len = min(n-1-l, r);
        
        /*
        move the two pointer i and j in their valid range,
        i.e. keep the two subarrays in both sides,
        and remove the subarray in the middle
        */
        for(int i = 0, j = r; i <= l && j < n; ++i){
            while(j < n && arr[i] > arr[j]){
                ++j;
            }
            
            if(j < n){
                //now arr[i] <= arr[j]
                //remove [i+1...j-1]
                min_len = min(min_len, j-1-i);
            }
        }
        
        return min_len;
    }
};
