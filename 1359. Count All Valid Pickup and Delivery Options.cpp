//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Count All Valid Pickup and Delivery Options.
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
