//Runtime: 48 ms, faster than 91.08% of C++ online submissions for Palindrome Number.
//Memory Usage: 8.2 MB, less than 99.22% of C++ online submissions for Palindrome Number.

class Solution {
public:
    bool isPalindrome(int x) {
        string s = to_string(x);
        int N = s.size();
        for(int i = 0; i < N; i++){
            if(s[i] != s[N-1-i]) return false;
        }
        return true;
    }
};

/**
Approach 1: Revert half of the number
**/

/**
Complexity Analysis
Time complexity : O(\log_{10}(n)). We divided the input by 10 for every iteration, so the time complexity is O(\log_{10}(n))
Space complexity : O(1).
**/

/**
class Solution {
public:
    bool isPalindrome(int x) {
        //if x is negative, there will be a '-' sign
        //if x's last digit is 0, then x must be 0
        if(x < 0 || (x != 0 && x%10 == 0)) return false;
        
        int reverted = 0;
        //construct reverted number of last half of x
        //do until reverted >= x
        while(x > reverted){
            reverted = reverted*10 + x%10;
            x/=10;
        }
        
        //if x has odd digits, 
        //we need to use /10 to get rid of the middle digit
        //(which is last digit in reverted)
        return x==reverted || x==reverted/10;
    }
};
**/
