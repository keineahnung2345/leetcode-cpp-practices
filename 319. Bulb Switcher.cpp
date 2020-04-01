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

//count divisor
//TLE
//30 / 35 test cases passed.
class Solution {
public:
    vector<int> divisorCount;
    
    int getDivisorCount(int n){
        if(divisorCount[n] == 0){
            int count = 0; //1
            double sqrt_n = sqrt(n);
            
            for(int i = 1; i <= sqrt_n; i++){
                if(n % i == 0){
                    if(i == sqrt_n) count++;
                    else count += 2;
                }
            }
            
            divisorCount[n] = count;
        }
        return divisorCount[n];
    };
    
    int bulbSwitch(int n) {
        //sum of divisor count from 1 to n
        divisorCount = vector<int>(n+1, 0);
        int ans = 0;
        
        for(int i = 1; i <= n; i++){
            int count = getDivisorCount(i);
            // cout << i << " " << count << endl;
            if(count % 2 == 1){
                ans++;
            }
        }
        
        return ans;
    }
};
