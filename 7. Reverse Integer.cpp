//Runtime: 4 ms, faster than 55.26% of C++ online submissions for Reverse Integer.
//Memory Usage: 6.2 MB, less than 12.99% of C++ online submissions for Reverse Integer.
class Solution {
public:
    int reverse(int x) {
        bool neg = false;
        if(x < 0){
            neg = true;
            long long tmp = x * -1LL;
            //consider -2147483648
            if(tmp > INT_MAX) return 0;
            x = tmp;
        }
        
        int ans = 0;
        
        while(x){
            long long tmp = ans * 10LL + x % 10;
            //consider 1534236469
            if(tmp > INT_MAX) return 0;
            ans = tmp;
            x /= 10;
        }
        
        if(neg){
            ans *= -1;
        }
        
        return ans;
    }
};

//Approach 1: Pop and Push Digits & Check before Overflow
//Runtime: 4 ms, faster than 55.26% of C++ online submissions for Reverse Integer.
//Memory Usage: 6.1 MB, less than 22.79% of C++ online submissions for Reverse Integer.
//time: O(log10(x)), space: O(1)
class Solution {
public:
    int reverse(int x) {
        int ans = 0;
        
        while(x){
            int pop = x%10;
            x /= 10;
            
            //>7 because the last digit of INT_MAX is 7
            //if ans*10 > INT_MAX or ans*10+pop > INT_MAX
            if(ans > INT_MAX/10 || (ans == INT_MAX/10 && pop > 7))
                return 0;
            
            //<-8 because the last digit of INT_MIN is 8
            //if ans*10 < INT_MIN or ans*10+pop < INT_MIN
            if(ans < INT_MIN/10 || (ans == INT_MIN/10 && pop < -8))
                return 0;
            
            ans = ans*10 + pop;
        }
        
        return ans;
    }
};
