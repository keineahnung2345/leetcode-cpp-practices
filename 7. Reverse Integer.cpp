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
