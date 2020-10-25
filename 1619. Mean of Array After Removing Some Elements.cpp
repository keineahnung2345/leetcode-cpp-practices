//Runtime: 28 ms, faster than 11.60% of C++ online submissions for Mean of Array After Removing Some Elements.
//Memory Usage: 10 MB, less than 99.83% of C++ online submissions for Mean of Array After Removing Some Elements.
class Solution {
public:
    double trimMean(vector<int>& arr) {
        int n = arr.size();
        
        int rem = n*5.0/100;
        
        sort(arr.begin(), arr.end());
        
        return (double)accumulate(arr.begin()+rem, arr.end()-rem, 0)/(n-2*rem);
    }
};
