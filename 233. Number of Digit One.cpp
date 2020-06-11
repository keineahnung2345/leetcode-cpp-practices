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

//DP
//not understand
//https://leetcode.com/problems/number-of-digit-one/discuss/254596/My-dynamic-programming-java-solution
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Number of Digit One.
//Memory Usage: 6.3 MB, less than 8.98% of C++ online submissions for Number of Digit One.
class Solution {
public:
    int countDigitOne(int n) {
        /*
        memo[i]: how many '1' in ith position (1-based)
        memo[0]: 0
        memo[1](one digit 0-9): 0*10+1 = 1
        memo[2](two digits 0-99): 1*10+10 = 20
        (00-09, 10-19, ..., 90-99)'s 1st digit + 10-19's 2nd digit
        memo[3](three digits 0-999): 20*10 + 100 = 300
        (000-099, 100-199, ..., 900-999)'s 1st and 2nd digits + 100-199's 3rd digit
        */
        vector<long long> memo(11);
        int rest = n;
        long long base = 1;
        
        for(int i = 1; rest > 0; i++){
            memo[i] = memo[i-1] * 10 + base;
            base *= 10;
            rest /= 10;
            // cout << rest << ", " << base << endl;
        }
        
        rest = n;
        base = 1e9;
        int index = log10(base)+1;
        int ans = 0;
        
        while(rest > 0 && index >= 1){
            if(rest >= base){
                int dividend = rest/base;
                rest %= base;
                // cout << "rest: " << rest << ", base: " << base << endl;
                if(dividend == 1){
                    ans += memo[index-1] + rest + 1;
                    // cout << index << ", " << memo[index-1] << ", " << rest << ", " << ans << endl;
                }else{
                    ans += memo[index-1] * dividend + base;
                    // cout << index << ", " << memo[index-1] << ", " << dividend << ", " << base << ", " << ans << endl;
                }
            }
            index--;
            base /= 10;
        }
        // cout << endl;
        
        return ans;
    }
};
