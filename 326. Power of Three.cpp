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

//Approach 1: Loop Iteration
//time: O(log3(n)), space: O(1)
//Runtime: 28 ms, faster than 17.10% of C++ online submissions for Power of Three.
//Memory Usage: 7.2 MB, less than 100.00% of C++ online submissions for Power of Three.
class Solution {
public:
    bool isPowerOfThree(int n) {
        if(n < 1) return false;
        
        while(n % 3 == 0){
            n /= 3;
        }
        
        return n == 1;
    }
};

//Approach 2: Base Conversion & regex
//time: O(log3(n)), space: O(log3(n))
//Runtime: 188 ms, faster than 5.75% of C++ online submissions for Power of Three.
//Memory Usage: 85.7 MB, less than 9.52% of C++ online submissions for Power of Three.
class Solution {
public:
    bool isPowerOfThree(int n) {
        // char buffer[32];
        // itoa(n, buffer, 3);
        // string str = string(buffer);
        
        string str = "";
        while(n){
            // str = to_string(n%3) + str;
            str.insert(0, to_string(n%3));
            n /= 3;
        }
        
        regex pattern("^10*$");
        
        return regex_match(str, pattern);
    }
};

//Approach 3: Mathematics
//time: depends on log's implementation, space: O(1)
//Runtime: 16 ms, faster than 69.14% of C++ online submissions for Power of Three.
//Memory Usage: 7.6 MB, less than 100.00% of C++ online submissions for Power of Three.
class Solution {
public:
    bool isPowerOfThree(int n) {
        // cout << n << ", " << round(log(n)/log(3)) << ", " << abs(round(log(n)/log(3)) - log(n)/log(3)) << ", " << std::numeric_limits<double>::epsilon() << endl;
        return abs(round(log(n)/log(3)) - log(n)/log(3)) < std::numeric_limits<double>::epsilon()*20;
    }
};

//Approach 4: Integer Limitations
//time: O(1), space: O(1)
//Runtime: 12 ms, faster than 86.75% of C++ online submissions for Power of Three.
//Memory Usage: 7.1 MB, less than 100.00% of C++ online submissions for Power of Three.
class Solution {
public:
    bool isPowerOfThree(int n) {
        int max_power_of_3 = pow(3, int(log(INT_MAX)/log(3)));
        //if n can divide max_power_of_3, it's power of 3
        return n > 0 && max_power_of_3 % n == 0;
    }
};
