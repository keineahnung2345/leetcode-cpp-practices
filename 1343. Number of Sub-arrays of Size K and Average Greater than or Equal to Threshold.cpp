//Runtime: 120 ms, faster than 68.15% of C++ online submissions for Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold.
//Memory Usage: 15.5 MB, less than 100.00% of C++ online submissions for Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold.

class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int N = arr.size();
        int cumSum = accumulate(arr.begin(), arr.begin()+k, 0);
        int ans = 0;
        
        for(int i = 0, cumSum = accumulate(arr.begin(), arr.begin()+k, 0); i+k-1 < N; i++){
            if(cumSum >= threshold * k) ans++;
            cumSum += -arr[i];
            if(i+k < N) cumSum += arr[i+k];
        }
        
        return ans;
    }
};
