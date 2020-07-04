//DP
//https://leetcode.com/problems/ugly-number-ii/discuss/69364/My-16ms-C%2B%2B-DP-solution-with-short-explanation
//Runtime: 32 ms, faster than 36.62% of C++ online submissions for Ugly Number II.
//Memory Usage: 7.8 MB, less than 59.06% of C++ online submissions for Ugly Number II.
class Solution {
public:
    int nthUglyNumber(int n) {
        if(n <= 0) return 0;
        if(n == 1) return 1;
        
        vector<int> dp(n);
        int t2 = 0, t3 = 0, t5 = 0;
        
        dp[0] = 1;
        for(int i = 1; i < n; ++i){
            dp[i] = min({dp[t2]*2, dp[t3]*3, dp[t5]*5});
            /*
            when we go from 
            "t2: 2, t3: 1, t5: 1, i: 4, val: 5"
            to 
            "t2: 3, t3: 2, t5: 1, i: 5, val: 6",
            both t2 and t3 are increased,
            because 6 = dp[2]*2 = dp[1]*3 
            (dp[2] = 2, dp[3] = 3)
            we increase both t2 and t3 so that 6 won't be 
            visited again
            */
            if(dp[i] == dp[t2]*2) ++t2;
            if(dp[i] == dp[t3]*3) ++t3;
            if(dp[i] == dp[t5]*5) ++t5;
            // cout << "t2: " << t2 << ", t3: " << t3 << ", t5: " << t5 << ", i: " << i << ", val: " << dp[i] << endl;
        }
        
        return dp[n-1];
    }
};

//priority queue
//https://leetcode.com/problems/ugly-number-ii/discuss/69397/Sharing-very-simple-and-elegant-Python-solution-using-heap-with-explanation
//Runtime: 904 ms, faster than 5.03% of C++ online submissions for Ugly Number II.
//Memory Usage: 36.2 MB, less than 5.06% of C++ online submissions for Ugly Number II.
class Solution {
public:
    int nthUglyNumber(int n) {
        //val, last multiplied factor
        //the smaller val should be popped first
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        
        vector<vector<int>> primes = {{2,INT_MAX/2},
                                      {3,INT_MAX/3},
                                      {5, INT_MAX/5}};
        
        int val = 1, fact = 1;
        int multiplier, upperLimit;
        
        pq.push({val, fact});
        
        for(int i = 0; i < n; ++i){
            vector<int> t = pq.top(); pq.pop();
            val = t[0];
            fact = t[1];
            // cout << "val: " << val << ", fact: " << fact << endl;
            
            for(int i = 0; i < primes.size(); ++i){
                multiplier = primes[i][0];
                upperLimit = primes[i][1];
                /*
                consider the number 6 = 2*3 = 3*2,
                if can be formed of (val=2)*(multiplier=3) or
                (val=3)*(multiplier=2),
                so there is a duplicate.
                To avoid the duplicate, we add a restriction that
                current multiplier should be >= fact.
                e.g. when val's last fact is 3, we won't multiply it by 2
                
                note: it works like the ascending permutation of prime numbers
                */
                if(multiplier >= fact && val < upperLimit){
                    pq.push({val*multiplier, multiplier});
                }
            }
        }
        
        return val;
    }
};
