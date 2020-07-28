//Runtime: 64 ms, faster than 40.58% of C++ online submissions for Bulb Switcher IV.
//Memory Usage: 10.3 MB, less than 100.00% of C++ online submissions for Bulb Switcher IV.
class Solution {
public:
    int minFlips(string target) {
        int n = target.size();
        
        string state(n, '0');
        int count = 0;
        bool flip = false;
        
        for(int i = 0; i < n; ++i){
            if(!flip && state[i] != target[i] || flip && state[i] == target[i]){
                ++count;
                flip = !flip;
            }
        }
        
        return count;
    }
};
