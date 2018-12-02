/**
A self-dividing number is a number that is divisible by every digit it contains.

For example, 128 is a self-dividing number because 128 % 1 == 0, 128 % 2 == 0, and 128 % 8 == 0.

Also, a self-dividing number is not allowed to contain the digit zero.

Given a lower and upper number bound, output a list of every possible self dividing number, including the bounds if possible.

Example 1:
Input: 
left = 1, right = 22
Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22]
Note:

The boundaries of each input argument are 1 <= left <= right <= 10000.
**/

//Your runtime beats 100.00 % of cpp submissions.
class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> result;
        for(int num = left; num <= right; num++){
            bool selfDividing = true;
            int workNum = num;
            while(workNum){
                //n-th digit is 0 or n-th digit of "num" cannot divide "num"
                if(workNum%10==0 || num%(workNum%10)!=0){
                    selfDividing = false;
                    break;
                }
                //if workNum<10, there won't be next iteration
                workNum/=10;
            }
            if(selfDividing) result.push_back(num);
        }
        return result;
    }
};

/**
Approach #1: Brute Force [Accepted]
Intuition and Algorithm

For each number in the given range, we will directly test if that number is self-dividing.

By definition, we want to test each whether each digit is non-zero and divides the number. For example, with 128, we want to test d != 0 && 128 % d == 0 for d = 1, 2, 8. To do that, we need to iterate over each digit of the number.

A straightforward approach to that problem would be to convert the number into a character array (string in Python), and then convert back to integer to perform the modulo operation when checking n % d == 0.

We could also continually divide the number by 10 and peek at the last digit. That is shown as a variation in a comment.

//Java
class Solution {
    public List<Integer> selfDividingNumbers(int left, int right) {
        List<Integer> ans = new ArrayList();
        for (int n = left; n <= right; ++n) {
            if (selfDividing(n)) ans.add(n);
        }
        return ans;
    }
    public boolean selfDividing(int n) {
        for (char c: String.valueOf(n).toCharArray()) {
            if (c == '0' || (n % (c - '0') > 0))
                return false;
        }
        return true;
    }
    /*
    Alternate implementation of selfDividing:
    public boolean selfDividing(int n) {
        int x = n;
        while (x > 0) {
            int d = x % 10;
            x /= 10;
            if (d == 0 || (n % d) > 0) return false;
        }
        return true;
    */
}

Complexity Analysis

Time Complexity: O(D), where D is the number of integers in the range [L, R], 
and assuming log(R) is bounded. (In general, the complexity would be O(DlogR).)

Space Complexity: O(D), the length of the answer.
