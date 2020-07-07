//Runtime: 4 ms, faster than 99.59% of C++ online submissions for Can Make Arithmetic Progression From Sequence.
//Memory Usage: 8.9 MB, less than 100.00% of C++ online submissions for Can Make Arithmetic Progression From Sequence.
class Solution {
public:
    bool canMakeArithmeticProgression(vector<int>& arr) {
        int n = arr.size();
        if(n <= 2) return true;
        
        sort(arr.begin(), arr.end());
        
        int diff = arr[1] - arr[0];
        
        for(int i = 1; i+1 < n; ++i){
            if(arr[i+1] - arr[i] != diff){
                return false;
            }
        }
        
        return true;
    }
};
