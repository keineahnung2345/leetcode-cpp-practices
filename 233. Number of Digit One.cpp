//Math
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Number of Digit One.
//Memory Usage: 6.1 MB, less than 27.55% of C++ online submissions for Number of Digit One.
//time: O(log_10(n)), space: O(1)
class Solution {
public:
    int countDigitOne(int n) {
        int ans = 0;
        
        /*
        for the example 1234:
        there are 123(0001,0011,0021,...,1221) +  
        1(1231) '1' in 'one' position
        there are 1234/100*10(0010-0019, 0110-0119, 1110-1119) + 
        10(1210-1219) '1' in 'ten' position
        there are 1234/1000*100=100(0100-0199) + 
        100(1100-1199) '1' in 'hundred' position
        there are 0 +
        235(1000-1234) '1' in 'thousand' position
        */
        
        for(long long i = 1; i <= n; i*=10){
            /*
            (n/(i*10))*i: count of '1' in ith(1-based) position 
            from 0 to n/(i*10)*(i*10)
            min(max(n%(i*10)-i+1, 0), i): from n/(i*10)*(i*10)+1 to n
            */
            ans += (n/(i*10))*i + min(max(n%(i*10)-i+1, 0LL), i);
        }
        
        return ans;
    }
}; 
