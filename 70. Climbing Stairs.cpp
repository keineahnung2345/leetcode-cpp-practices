//DP
/**
Complexity Analysis
Time complexity : O(n)O(n). Single loop upto nn.
Space complexity : O(n)O(n). dpdp array of size nn is used. 
**/
//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Climbing Stairs.
//Memory Usage: 8.5 MB, less than 55.79% of C++ online submissions for Climbing Stairs.
class Solution {
public:
    int climbStairs(int n) {
        if(n == 1) return 1;
        vector<int> steps(n);
        
        // cout << "size: " << steps.size() << endl;
        
        steps[0] = 1; //1+0 step from the top
        steps[1] = 2; //1+1 step from the top
        
        for(int i = 2; i < n; i++){
            steps[i] = steps[i-1] + steps[i-2];
            // cout << steps[i] << endl;
        }
        
        return steps[n-1];
    }
};

//Fibonacci number
/**
Complexity Analysis
Time complexity : O(n)O(n). Single loop upto nn is required to calculate n^{th}n 
th fibonacci number.
Space complexity : O(1)O(1). Constant space is used. 
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Climbing Stairs.
//Memory Usage: 8.2 MB, less than 97.68% of C++ online submissions for Climbing Stairs.
class Solution {
public:
    int climbStairs(int n) {
        if(n <= 2) return n;
        
        int last = 1, last2 = 2;
        
        for(int i = 2; i < n; i++){
            int tmp = last2;
            last2 = last + last2;
            last = tmp;
            // cout << last << " " << last2 << endl;
        }
        // cout << endl;
        
        return last2;
    }
};

//DP and Fibonacci, no edge case
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Climbing Stairs.
//Memory Usage: 5.9 MB, less than 100.00% of C++ online submissions for Climbing Stairs.
class Solution {
public:
    int climbStairs(int n) {
        // vector<int> dp(n+1, 0);
        
        //0: padding, used when dp[2] = dp[1] + dp[0]
        // dp[0] = dp[1] = 1;
        int last1 = 1, last2 = 1;
        
        for(int i = 2; i <= n; i++){
            // dp[i] = dp[i-1] + dp[i-2];
            last2 += last1;
            swap(last1, last2);
        }
        
        // return dp[n];
        return last1;
    }
};

/**
Approach 5: Binets Method
**/

/**
Complexity Analysis
Time complexity : O(\log n)O(logn). Traversing on \log nlogn bits.
Space complexity : O(1)O(1). Constant space is used.
**/

/**
class Solution {
public:
    void multiply(const vector<vector<long long>>& a, const vector<vector<long long>>& b, vector<vector<long long>>& c){
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
            }
        }
    }
    
    void pow(vector<vector<long long>>& a, int n, vector<vector<long long>>& r){
        vector<vector<long long>> tmp = {{0,0}, {0,0}};
        while(n > 0){
            //if(n%2 == 1){
            if((n&1) == 1){
                multiply(r, a, tmp);
                r = tmp;
            }
            //n/=2;
            n >>= 1;
            multiply(a, a, tmp);
            a = tmp;
        }
    }
    
    int climbStairs(int n) {
        vector<vector<long long>> q = {{1,1}, {1,0}};
        vector<vector<long long>> r = {{1,0}, {0,1}};
        pow(q, n, r);
        return r[0][0];
    }
};
**/

/**
Approach 6: Fibonacci Formula
**/

/**
Complexity Analysis

Time complexity : O(\log n)O(logn). powpow method takes \log nlogn time.

Space complexity : O(1)O(1). Constant space is used.
**/

/**
class Solution {
public:
    int climbStairs(int n) {
        double sqrt5 = sqrt(5);
        double fibn = pow((1+sqrt5)/2, n+1) - pow((1-sqrt5)/2, n+1);
        return (int)(fibn/sqrt5);
    }
};
**/
