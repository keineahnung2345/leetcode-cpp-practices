//Runtime: 4 ms, faster than 98.79% of C++ online submissions for Find N Unique Integers Sum up to Zero.
//Memory Usage: 8.6 MB, less than 100.00% of C++ online submissions for Find N Unique Integers Sum up to Zero.

class Solution {
public:
    vector<int> sumZero(int n) {
        vector<int> ans;
        
        if(n % 2 == 1){
            ans.push_back(0);
            n--;
        }
        
        for(int i = 1; i <= n/2; i++){
            ans.push_back(i);
            ans.push_back(-i);
        }
        
        return ans;
    }
};
