//Runtime: 4 ms, faster than 23.29% of C++ online submissions for Pow(x, n).
//Memory Usage: 6.1 MB, less than 20.88% of C++ online submissions for Pow(x, n).
class Solution {
public:
    double myPow(double x, int n) {
        return pow(x, n);
    }
};

//divide and conquer, recursion
//https://leetcode.com/problems/powx-n/discuss/19546/Short-and-easy-to-understand-solution
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Pow(x, n).
//Memory Usage: 5.9 MB, less than 95.42% of C++ online submissions for Pow(x, n).
class Solution {
public:
    double myPow(double x, int n) {
        if(n == 0){
            return 1;
        }
        
        if(n == INT_MIN){
            /*
            if n is INT_MIN(-2147483648),
            -n will exceed INT_MAX(2147483647),
            leading overflow
            
            we can avoid overflow by adding INT_MIN by 1,
            because -2147483648/2 is the same as (-2147483648+1)/2
            */
            ++n;
            n *= -1;
            x = 1/x;
            return myPow(x*x, n/2);
        }
        
        if(n < 0){
            if(n == INT_MIN) ++n;
            n *= -1;
            x = 1/x;
        }
        
        return myPow(x*x, n/2) * (n%2 ? x : 1);
    }
};

//iterative
//https://leetcode.com/problems/powx-n/discuss/19544/5-different-choices-when-talk-with-interviewers
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Pow(x, n).
//Memory Usage: 6 MB, less than 60.70% of C++ online submissions for Pow(x, n).
class Solution {
public:
    double myPow(double x, int n) {
        if(n == 0 || x == 1){
            return 1;
        }
        
        double ans = 1.0;
        
        if(n == INT_MIN){
            //take -1 power away
            ans /= x;
            ++n;
            n *= -1;
            x = 1.0/x;
        }else if(n < 0){
            n *= -1;
            x = 1.0/x;
        }
        
        while(n){
            if(n & 1){
                ans *= x;
            }
            
            x *= x;
            n >>= 1;
        }
        
        return ans;
    }
};
