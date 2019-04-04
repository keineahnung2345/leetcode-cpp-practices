//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Valid Perfect Square.
//Memory Usage: 8 MB, less than 83.44% of C++ online submissions for Valid Perfect Square.

class Solution {
public:
    bool isPerfectSquare(int num) {
        long long lnum = num;
        for(long long i = 1; i * i <= lnum; i++){
            if(i * i == lnum) return true;
        }
        return false;
    }
};

//https://leetcode.com/problems/valid-perfect-square/discuss/83874/A-square-number-is-1%2B3%2B5%2B7%2B...-JAVA-code
/**
Approach 1 :A square number is 1+3+5+7+...
O(sqrt(n))
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Valid Perfect Square.
//Memory Usage: 8 MB, less than 64.42% of C++ online submissions for Valid Perfect Square.

class Solution {
public:
    bool isPerfectSquare(int num) {
        int i = 1;
        while(num > 0){
            num -= i;
            i += 2;
        }
        return num == 0;
    }
};

/**
Approach 2 : binary search
O(logn)
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Valid Perfect Square.
//Memory Usage: 8.1 MB, less than 55.21% of C++ online submissions for Valid Perfect Square.

class Solution {
public:
    bool isPerfectSquare(int num) {
        long long low = 1, high = num;
        while(low <= high){
            long long mid = (low+high) >> 1;
            if(mid * mid == num){
                return true;
            }else if(mid * mid < num){
                low = mid + 1;
            }else{
                high = mid - 1;
            }
        }
        return false;
    }
};

/**
Approach 3 : Newtown method
**/

/Runtime: 4 ms, faster than 100.00% of C++ online submissions for Valid Perfect Square.
//Memory Usage: 8.1 MB, less than 50.92% of C++ online submissions for Valid Perfect Square.

class Solution {
public:
    bool isPerfectSquare(int num) {
        long long x = num;
        while(x * x > num){
            x = (x + num/x) >> 1;
        }
        return x*x == num;
    }
};
