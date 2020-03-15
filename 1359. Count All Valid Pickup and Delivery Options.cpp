//https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/discuss/516968/JavaC%2B%2BPython-Easy-and-Concise
//Recursion
/Runtime: 0 ms, faster than 100.00% of C++ online submissions for Count All Valid Pickup and Delivery Options.
//Memory Usage: 7.4 MB, less than 100.00% of C++ online submissions for Count All Valid Pickup and Delivery Options.

class Solution {
public:
    int rCountOrders(int n, long res){
        return n > 0 ? rCountOrders(n-1, res * (2*n-1) * n % (long(1e9 + 7))) : res;
        //overflow
        // return n > 0 ? (2*n-1) * (2*n) /2 * rCountOrders(n-1, res) % long(pow(10, 9) + 7) : res;
    };
    
    int countOrders(int n) {
        return rCountOrders(n, 1);
    }
};

//Bottom-up
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Count All Valid Pickup and Delivery Options.
//Memory Usage: 7.5 MB, less than 100.00% of C++ online submissions for Count All Valid Pickup and Delivery Options.
class Solution {
public:
    int countOrders(int n) {
        //use long to avoid overflow
        long res = 1, mod = 1e9+7;
        
        for(int i = 1; i <= n; i++){
            res = res * (2*i-1) * i % mod;
        }
        
        return (int)res;
    }
};
