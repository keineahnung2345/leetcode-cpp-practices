/**
X is a good number if after rotating each digit individually by 180 degrees, we get a valid number that is different from X.  Each digit must be rotated - we cannot choose to leave it alone.

A number is valid if each digit remains a digit after rotation. 0, 1, and 8 rotate to themselves; 2 and 5 rotate to each other; 6 and 9 rotate to each other, and the rest of the numbers do not rotate to any other number and become invalid.

Now given a positive number N, how many numbers X from 1 to N are good?

Example:
Input: 10
Output: 4
Explanation: 
There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
Note:

N  will be in range [1, 10000].
**/

//Runtime: 8 ms, faster than 57.61% of C++ online submissions for Rotated Digits.
//Memory Usage: 8.4 MB, less than 70.37% of C++ online submissions for Rotated Digits.

class Solution {
public:
    bool isGood(int n){
        bool isDifferent = false;
        while(n>0){
            int last = n%10;
            
            if(last==2 || last==5 || last==6 || last==9){
                isDifferent = true;
            }else if(last==0 || last==1 || last==8){
                //pass
            }else{
                return false;
            }
            n/=10;
        }
        return isDifferent;
    }
    int rotatedDigits(int N) {
        int ans = 0;
        
        for(int n = 1; n <=N ; n++){
            if(isGood(n)){
                ans++;
            }
        }
        return ans;
    }
};
