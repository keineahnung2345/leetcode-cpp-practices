//bit operation
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        if(m == 0) return 0;
        //log(0) is not defined
        int mb = log2(m), nb = log2(n);
        
        if(mb != nb) return 0;
        
        int ans = 0;
        
        //examine one bit at a time
        while(mb == nb){
            //remove that bit once examined
            ans += (1 << mb);
            m -= (1 << mb);
            n -= (1 << mb);
            if(m == 0) break;
            mb = log2(m);
            nb = log2(n);
        };
        
        return ans;
    }
};

//https://leetcode.com/explore/challenge/card/30-day-leetcoding-challenge/531/week-4/3308/discuss/593317/Simple-3-line-Java-solution-faster-than-100
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        while(n > m){
            /*
            suppose a >= b
            the result of a & b must <= min(a, b) = b,
            so we can skip numbers between b and (a&b)
            */
            n &= (n-1);
        }
        return n & m;
    }
};
