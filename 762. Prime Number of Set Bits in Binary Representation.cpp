/**
Given two integers L and R, find the count of numbers in the range [L, R] (inclusive) having a prime number of set bits in their binary representation.

(Recall that the number of set bits an integer has is the number of 1s present when written in binary. For example, 21 written in binary is 10101 which has 3 set bits. Also, 1 is not a prime.)

Example 1:

Input: L = 6, R = 10
Output: 4
Explanation:
6 -> 110 (2 set bits, 2 is prime)
7 -> 111 (3 set bits, 3 is prime)
9 -> 1001 (2 set bits , 2 is prime)
10->1010 (2 set bits , 2 is prime)
Example 2:

Input: L = 10, R = 15
Output: 5
Explanation:
10 -> 1010 (2 set bits, 2 is prime)
11 -> 1011 (3 set bits, 3 is prime)
12 -> 1100 (2 set bits, 2 is prime)
13 -> 1101 (3 set bits, 3 is prime)
14 -> 1110 (3 set bits, 3 is prime)
15 -> 1111 (4 set bits, 4 is not prime)
Note:

L, R will be integers L <= R in the range [1, 10^6].
R - L will be at most 10000.
**/

//Runtime: 36 ms, faster than 34.99% of C++ online submissions for Prime Number of Set Bits in Binary Representation.
//Memory Usage: 9.4 MB, less than 44.61% of C++ online submissions for Prime Number of Set Bits in Binary Representation.
class Solution {
public:
    int countSetBits(int n){
        int counts = 0;
        while(n!=0){
            counts+=(n%2);
            n/=2;
        }
        // cout << counts << " ";
        return counts;
    }
    
    bool checkIsPrime(int n){
        if(n==1) return false;
        int sqr = floor(sqrt(n));
        while(sqr>1){
            //check whether n is divisible by 2,3,5,...
            if(n%sqr==0){
                return false;
            }
            sqr--;
        }
        return true;
    }
    
    int countPrimeSetBits(int L, int R) {
        int ans = 0;
        for(int n = L; n <= R; n++){
            if(checkIsPrime(countSetBits(n))){
                ans++;
            }
        }
        // cout << endl;
        return ans;
    }
};

/**
Approach #1: Direct [Accepted]
Intuition and Approach

For each number from L to R, let's find out how many set bits it has.
If that number is 2, 3, 5, 7, 11, 13, 17, or 19, then we add one to our count. 
We only need primes up to 19 because R<=10^6<=2^20.
 **/
 
/**
Complexity Analysis

Time Complexity: O(D), where D = R-L is the number of integers considered.
In a bit complexity model, this would be O(DlogD) as we have to count the bits in O(logD) time.

Space Complexity: O(1).
**/

//method1
//Runtime: 1220 ms, faster than 5.23% of C++ online submissions for Prime Number of Set Bits in Binary Representation.
//Memory Usage: 361.2 MB, less than 6.15% of C++ online submissions for Prime Number of Set Bits in Binary Representation.

//method2
//Runtime: 8 ms, faster than 99.45% of C++ online submissions for Prime Number of Set Bits in Binary Representation.
//Memory Usage: 9.4 MB, less than 44.61% of C++ online submissions for Prime Number of Set Bits in Binary Representation.

/**
class Solution {
public:
    bool isSmallPrime(int n){
        //method1
        // set<int> smallPrimes = {2,3,5,7,11,13,17,19};
        // return smallPrimes.find(n)!=smallPrimes.end();
        
        //method2
        return n==2 || n==3 || n==5 || n==7 || n==11 || n==13 || n==17 || n==19;
    }
    int countPrimeSetBits(int L, int R) {
        int ans = 0;
        for(int n = L; n <= R; n++){
            bitset<20> b(n);
            if(isSmallPrime(b.count())){
                ans++;
            }
        }
        return ans;
    }
};
**/
