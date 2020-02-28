//Runtime: 28 ms, faster than 17.10% of C++ online submissions for Power of Three.
//Memory Usage: 8.2 MB, less than 76.19% of C++ online submissions for Power of Three.
class Solution {
public:
    bool isPowerOfThree(int n) {
        if(n == 1) return true;
        if(n == 0) return false;
        if(n % 3 != 0) return false;
        return isPowerOfThree(n/3);
    }
};

//log
//Runtime: 16 ms, faster than 69.14% of C++ online submissions for Power of Three.
//Memory Usage: 8.6 MB, less than 9.52% of C++ online submissions for Power of Three.
class Solution {
public:
    bool isPowerOfThree(int n) {
        if(n == 0) return false;
        // cout << (log(n) / log(3)) << ", " << (log(n) / log(3)) - ceil((log(n) / log(3))) << endl;
        //ceil: round up
        //<1e-14: double precision 
        return abs((log(n) / log(3)) - ceil((log(n) / log(3)))) < 1e-14;
    }
};
