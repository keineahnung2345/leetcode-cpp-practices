//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Powerful Integers.
//Memory Usage: 7.7 MB, less than 100.00% of C++ online submissions for Powerful Integers.

class Solution {
public:
    vector<int> powerfulIntegers(int x, int y, int bound) {
        vector<int> ans;
        int pi = 0;
            
        for(int i = 0; pow(x, i) + pow(y, 0) <= bound; i++){
            if(x == 1 && pi == pow(x, i) + pow(y, 0)) break;
            for(int j = 0; pow(x, i) + pow(y, j) <= bound; j++){
                if(y == 1 && pi == pow(x, i) + pow(y, j)) break;
                pi = pow(x, i) + pow(y, j);
                if(pi <= bound && 
                   find(ans.begin(), ans.end(), pi) == ans.end()){
                    ans.push_back(pi);
                }
            }
            pi = pow(x, i) + pow(y, 0);
        }
        
        return ans;
    }
};
