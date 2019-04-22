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

//binary search
//AddressSanitizer:DEADLYSIGNAL
//time: O(sqrt(c) * log(c))
//space: O(log(c)), space used by binary search

class Solution {
public:
    bool binary_search(long long s, long long e, long long n){
        if(s > e) return false;
        long long mid = (s + e)/2;
        if(mid * mid == n) return true;
        if(mid * mid > n){
            return binary_search(s, e-1, n);
        }
        return binary_search(s+1, e, n);
    }
    
    bool judgeSquareSum(int c) {
        for(long long a = 0; a * a <= (long long)c; a++){
            long long b = c - (a*a);
            if(binary_search(0, b, b)) return true;
        }
        return false;
    }
};

//Fermat theorem
//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Sum of Square Numbers.
//Memory Usage: 8.1 MB, less than 100.00% of C++ online submissions for Sum of Square Numbers.
//time: O(sqrt(c) * log(c)), sqrt(c) candidates of factor, a factor can occur at most log(c) times
//space: O(1)
class Solution {
public:
    bool judgeSquareSum(int c) {
        //check for factor in the range [2, sqrt(c)]
        for(int p = 2; p*p <= c; p++){
            //p : candidate prime factor of c
            int count = 0;
            if(c % p == 0){ //p is a prime factor of c 
                //every time we find a prime factor,
                // we divide c by p so that c won't have p as factor anymore
                //the maximum time a factor can occur is log(c)
                while(c % p == 0){
                    count++;
                    c /= p;
                }
                if(p % 4 == 3 && count % 2 != 0){
                    return false;
                }
            }
        }
        return c % 4 != 3;
    }
};
