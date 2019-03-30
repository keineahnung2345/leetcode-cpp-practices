/**
Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example: 

Input: 19
Output: true
Explanation: 
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Happy Number.
//Memory Usage: 8.4 MB, less than 57.57% of C++ online submissions for Happy Number.
class Solution {
public:
    bool isHappy(int n) {
        int tmp = 0;
        set<int> visited;
        
        while(true){
            tmp = 0;
            while(n > 0){
                tmp += pow((n%10), 2);
                n/=10;
            }
            n = tmp;
            if(n == 1){
                break;
            }else if(visited.find(n)!=visited.end()){
                return false;
            }
            visited.insert(n);
        }
        return true;
    }
};
