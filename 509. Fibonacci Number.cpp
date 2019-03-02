/**
The Fibonacci numbers, commonly denoted F(n) form a sequence, 
called the Fibonacci sequence, 
such that each number is the sum of the two preceding ones, 
starting from 0 and 1. That is,

F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), for N > 1.
Given N, calculate F(N).
**/

//Runtime: 16 ms, faster than 32.44% of C++ online submissions for Fibonacci Number.
//Memory Usage: 8.5 MB, less than 38.31% of C++ online submissions for Fibonacci Number.

//recursive solution
class Solution {
public:
    int fib(int N) {
        if(N==0 or N==1){
            return N;
        }else{
            return fib(N-1) + fib(N-2);
        }
    }
};

//dynamic programming
class Solution {
public:
    int fib(int N) {
        if(N==0 or N==1){
            return N;
        }
        vector<int> arr = {0, 1};
        while(arr.size() < N+1){
            arr.push_back(arr[arr.size()-1] + arr[arr.size()-2]);
        }
        return arr[arr.size()-1];
    }
};
