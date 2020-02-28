//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Guess Number Higher or Lower.
//Memory Usage: 7.3 MB, less than 100.00% of C++ online submissions for Guess Number Higher or Lower.

// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        int left = 1, right = n, cur = left+(right-left)/2;

        while(true){
            switch(guess(cur)){
                case -1:
                    right = cur-1;
                    cur = left+(right-left)/2;
                    break;
                case 1:
                    left = cur+1;
                    cur = left+(right-left)/2;
                    break;
                case 0:
                    return cur;
            }
        }
        return 0;
    }
};
