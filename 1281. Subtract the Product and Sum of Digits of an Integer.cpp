//Runtime: 4 ms, faster than 51.60% of C++ online submissions for Subtract the Product and Sum of Digits of an Integer.
//Memory Usage: 8.2 MB, less than 100.00% of C++ online submissions for Subtract the Product and Sum of Digits of an Integer.

class Solution {
public:
    int subtractProductAndSum(int n) {
        int product = 1, sum = 0;
        
        while(n > 0){
            int d = n%10;
            product *= d;
            sum += d;
            n /= 10;
        }
        
        return product - sum;
    }
};
