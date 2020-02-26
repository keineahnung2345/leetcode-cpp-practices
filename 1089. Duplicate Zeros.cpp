//Runtime: 40 ms, faster than 27.67% of C++ online submissions for Duplicate Zeros.
//Memory Usage: 9.5 MB, less than 100.00% of C++ online submissions for Duplicate Zeros.

class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int n = arr.size();
        
        for(int i = n-1; i >= 0; i--){
            if(arr[i] == 0){
                arr.insert(arr.begin() + i, 0);
            }
        }
        
        arr.resize(n);
    }
};
