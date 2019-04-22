//using sqrt function
//Runtime: 12 ms, faster than 25.09% of C++ online submissions for Sum of Square Numbers.
//Memory Usage: 7.9 MB, less than 100.00% of C++ online submissions for Sum of Square Numbers.
//time: O(sqrt(c) * log(c)), iterate sqrt(c) times, every iteration O(log(c)) to calculate sqrt
//space: O(1)

class Solution {
public:
    bool judgeSquareSum(int c) {
        for(int i = 0; i <= int(sqrt(c/2)); i++){
            if(sqrt(c - i*i) == int(sqrt(c - i*i))) return true;
        }
        return false;
    }
};

//better brute-force
//TLE
//time: Time complexity : O(c). The total number of times the sumsum is updated is: 1 + 2 + 3 + ... + sqrt(c) = (1+sqrt(c))*sqrt(c)/2 = O(c)
//Space complexity : O(1). Constant extra space is used. 

class Solution {
public:
    bool judgeSquareSum(int c) {
        for(long long a = 0; a*a <= c; a++){
            int b = c - (int)a*a;
            long long i = 1, sum = 0;
            while(sum < b){
                sum += i;
                i += 2;
            }
            if(sum == (long long)b) return true;
        }
        return false;
    }
};
