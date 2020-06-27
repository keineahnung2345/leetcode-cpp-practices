//sliding window, dp
//https://leetcode.com/problems/new-21-game/discuss/132334/One-Pass-DP-O(N)
//Runtime: 4 ms, faster than 81.06% of C++ online submissions for New 21 Game.
//Memory Usage: 9.3 MB, less than 52.69% of C++ online submissions for New 21 Game.
//time: O(N), space: O(N)
class Solution {
public:
    double new21Game(int N, int K, int W) {
        /*
        stop when drawing no cards,
        at this time, Alice has definitely <= N points
        */
        if(K == 0) return 1;
        /*
        since we stop drawing cards when we have K points,
        we can draw cards when we have K-1 points,
        and the maximum points we can get is K-1+W,
        if K-1+W <= N, then we will have N or less points we prob 1
        */
        if(K-1+W <= N) return 1;
        
        /*
        stops at K, which is larger than N,
        so the prob of having <= N ponits is 0
        */
        if(N < K) return 0;
        
        vector<double> dp(N+1, 0);
        
        //?
        dp[0] = 1;
        /*
        we can go from [i-W, i-1] to i by drawing one card
        Wsum is the sum of prob of dp[i-W] to dp[i-1]
        */
        double Wsum = 1; //?
        /*
        prob of getting points <= N,
        this is equivalent to sum of prob of getting [K,N]
        */
        double res = 0;
        
        for(int i = 1; i <= N; ++i){
            /*
            Wsum: sum of prob of reaching [i-W,i-1] points
            *1/W: multiplied by the prob of drawing 1(or 2, 3, ..., W)
            */
            dp[i] = Wsum/W;
            if(i < K){
                /*
                when we have i(less than K) points, 
                we can still draw card.
                This is done by accumulating its prob to Wsum
                */
                Wsum += dp[i];
            }else{
                /*
                when i reaches K, we stop drawing cards
                res: sum of dp[K] to dp[N]
                */
                res += dp[i];
            }
            if(i-W >= 0) Wsum -= dp[i-W];
        }
        
        return res;
    }
};
