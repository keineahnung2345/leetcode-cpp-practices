//Runtime: 0 ms, faster than 100.00% of C++ online submissions for 2 Keys Keyboard.
//Memory Usage: 6 MB, less than 100.00% of C++ online submissions for 2 Keys Keyboard.
//time: O(sqrt(n)), space: O(1)
class Solution {
public:
    /*
    our moves can be represented as [CP...PP][CP...P][CPP...P]...,
    say their lengths are g_1, g_2, .... g_n.
    
    now suppose we have x 'A's on screen,
    after [CP...PP] with length g_1,
    there will be x * g_1 A's on screen,
    so after all the moves: [CP...PP][CP...P][CPP...P]...,
    we have x * g_1 * g_2 * ... * g_n 'A's,
    and x is equal to 1, so we will have g_1 * g_2 * ... * g_n 'A's.
    
    to get exactly n 'A's, we can factor n to g_1 * g_2 * ... * g_n,
    and it takes g_1 + g_2 + ... + g_n moves.
    
    now we need to prove that split n into g_1 * g_2 * ... * g_n 
    only decreases the moves needed:
    say g_i = p*q, we want g_i <= p+q -> p*q <= p+q
    -> p*q-p-q <= 0 -> (p-1)*(q-1) <= 1,
    and this is true when p >= 2 and q >= 2,
    since our factorization stops when prime is equal to 2,
    so this always holds
    */
    int minSteps(int n) {
        int ans = 0;
        int prime = 2;
        
        while(n > 1){
            /*
            if prime is a composite, 
            it will skip this part,
            because now n's smallest prime factor is larger than prime
            */
            while(n % prime == 0){
                n /= prime;
                ans += prime;
            }
            //try to find next prime
            prime++;
        }
        
        return ans;
    }
};

//DP
//https://leetcode.com/problems/2-keys-keyboard/discuss/105899/Java-DP-Solution
//Runtime: 24 ms, faster than 35.04% of C++ online submissions for 2 Keys Keyboard.
//Memory Usage: 6.8 MB, less than 100.00% of C++ online submissions for 2 Keys Keyboard.
class Solution {
public:
    int minSteps(int n) {
        //dp[i]: how many moves we need to take in order to get i A's
        vector<int> dp(n+1, 0);
        
        //dp[1] is 0, 0 moves
        for(int i = 2; i <= n; i++){
            dp[i] = i;
            for(int j = i-1; j >= 2; j--){
                /*
                i A's can be generated from j A's
                by copy(1 move) and then paste i/j-1 times(i/j-1 moves),
                so dp[i] is the move to get j A's(dp[j]) plus i/j moves
                */
                if(i % j == 0){
                    dp[i] = dp[j] + i/j;
                    break;
                }
            }
        }
        
        return dp[n];
    }
};
