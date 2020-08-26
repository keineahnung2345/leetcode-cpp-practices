//TLE
class Solution {
public:
    int findNthDigit(int n) {
        string s = "";
        for(int i = 1; s.size() < n; i++){
            s += to_string(i);
        }
        return s[n-1]-'0';
    }
};

//Math
//https://leetcode.com/problems/nth-digit/discuss/88363/Java-solution
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Nth Digit.
//Memory Usage: 6.1 MB, less than 45.17% of C++ online submissions for Nth Digit.
class Solution {
public:
    int findNthDigit(int n) {
        int len = 1;
        long long count = 9; //1 to 9
        int num = 1;
        
        //look through 1-digit numbers, 2-digit numbers, ...
        while(n > len * count){
            n -= len*count;
            ++len;
            count *= 10;
            num *= 10;
        }
        
        /*
        for n = 195,
        we skip 1*9 + 2*90 = 189 numbers,
        so now n = 6(index start from 1),
        what we want is the 2nd 3-digit number,
        turn it into 0-based index, 
        it would be 1st(0-based) 3-digit number,
        we want the mapping:
        1,2,3 -> 0
        4,5,6 -> 1
        and (n-1)/len is just this!
        */
        // cout << num << ", " << n << endl;
        num += (n-1)/len;
        // cout << num << endl;
        
        return to_string(num)[(n-1)%len]-'0';
    }
};
