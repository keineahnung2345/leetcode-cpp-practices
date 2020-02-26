//Runtime: 4 ms, faster than 57.03% of C++ online submissions for N-th Tribonacci Number.
//Memory Usage: 8.4 MB, less than 100.00% of C++ online submissions for N-th Tribonacci Number.

class Solution {
public:
    int tribonacci(int n) {
        vector<int> arr(n+1);
        
        arr[0] = 0; 
        if(n >= 1)arr[1] = 1; 
        if(n >= 2)arr[2] = 1;
        
        for(int i = 3; i <= n; i++){
            arr[i] = arr[i-1] + arr[i-2] + arr[i-3];
        }
        
        return arr[n];
    }
};
