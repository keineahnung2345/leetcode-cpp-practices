//TLE
//31 / 35 test cases passed.
class Solution {
public:
    int bulbSwitch(int n) {
        if(n == 1) return 1;
        
        vector<bool> state(n, true);
        for(int t = 2; t <= n; t++){
            for(int i = t-1; i < n; i += t){
                // cout << state[i] << " " << (~state[i]) << " " << !state[i] << endl;
                //~: bitwise complement, !: not
                //~1 -> -2, !1 -> 0, so we should use "!" here
                state[i] = !state[i];
            }
        }
        
        // for(int i = 0; i < n; i++){
        //     cout << state[i] << " ";
        // }
        // cout << endl;
        
        return accumulate(state.begin(), state.end(), 0);
    }
};
