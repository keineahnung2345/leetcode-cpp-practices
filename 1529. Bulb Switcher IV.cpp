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

//we don't need an array for state, because the initial state for all positions are the same
//https://leetcode.com/problems/bulb-switcher-iv/discuss/755939/C%2B%2B-Python-Java%3A-Readable-easy-code-with-explanation-and-code-comments
//Runtime: 48 ms, faster than 81.67% of C++ online submissions for Bulb Switcher IV.
//Memory Usage: 9.4 MB, less than 100.00% of C++ online submissions for Bulb Switcher IV.
class Solution {
public:
    int minFlips(string target) {
        int n = target.size();
        
        char state = '0';
        int count = 0;
        bool flip = false;
        
        for(int i = 0; i < n; ++i){
            if(state != target[i]){
                ++count;
                flip = !flip;
                state = (state == '0') ? '1' : '0';
            }
        }
        
        return count;
    }
};
