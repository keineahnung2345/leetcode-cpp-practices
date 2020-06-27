//Pigeonhole principle
//https://leetcode.com/problems/smallest-integer-divisible-by-k/discuss/260875/Python-O(K)-with-Detailed-Explanations
//Runtime: 104 ms, faster than 7.42% of C++ online submissions for Smallest Integer Divisible by K.
//Memory Usage: 14.4 MB, less than 5.63% of C++ online submissions for Smallest Integer Divisible by K.
//time: O(K), space: O(K)
class Solution {
public:
    int smallestRepunitDivByK(int K) {
        set<int> viableLastDigits= {1,3,7,9};
        
        if(viableLastDigits.find(K%10) == viableLastDigits.end()){
            return -1;
        }
        
        int res = 0;
        set<int> resSet;
        
        /*
        the residuals of %K are [0,K-1],
        so we try out 1, 11, 111, 11..111(K '1's)
        to see if these numbers' residuals fill the holes
        
        if there is a duplicate before we find a residual = 0,
        it will produce a cycle so we will never
        find a number n s.t. n%K is 0
        
        the proof of cycle: n2_res = (10*n1_res + 1) % K,
        that means the residual of current number is dependent
        on the previous number
        */
        for(int len = 1; len <= K; ++len){
            res = (res * 10 + 1) % K;
            if(res == 0) return len;
            if(resSet.find(res) != resSet.end()) return -1;
            resSet.insert(res);
        }
        
        return -1;
    }
};
