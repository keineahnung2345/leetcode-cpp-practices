//TLE
//94 / 109 test cases passed.
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int n = A.size();
        
        vector<vector<int>> dp(n, vector(n, INT_MIN));
        int ans = INT_MIN;
        
        //i: start
        for(int i = n-1; i >= 0; i--){
            //j: end
            //the upper bound(exclusive) changes from n to i+n -> circular
            for(int j = i; j < i+n; j++){
                //length 1 subarray
                if(i == j){
                    dp[i][j%n] = A[i];
                }else{
                    dp[i][j%n] = max({dp[i][j%n], 
                                    (dp[(i+1)%n][j%n] == INT_MIN) ? INT_MIN : A[i]+dp[(i+1)%n][j%n], 
                                    (dp[i][(j-1+n)%n] == INT_MIN) ? INT_MIN : dp[i][(j-1+n)%n]+A[j%n]
                                    });
                }
                
                // if(dp[i][j%n] > ans){
                //     cout << "[" << i << ", " << j << "]: " << dp[i][j%n] << endl;
                // }
                ans = max(ans, dp[i][j%n]);
            }
        }
        
        return ans;
    }
};

//Kanade's Algorithm
//https://medium.com/@rsinghal757/kadanes-algorithm-dynamic-programming-how-and-why-does-it-work-3fd8849ed73d
//O(n)
/*
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int n = A.size();
        int localMax = INT_MIN; // max sum of subarray which ends at i
        int globalMax = INT_MIN;
        
        for(int i = 0; i < n; i++){
            //enlong the old subarray or create a new one starting from i
            localMax = max(A[i], (localMax == INT_MIN) ? INT_MIN : A[i] + localMax);
            globalMax = max(globalMax, localMax);
        }
        
        return globalMax;
    }
};
*/

//Approach 1: Next Array
//Runtime: 172 ms, faster than 8.63% of C++ online submissions for Maximum Sum Circular Subarray.
//Memory Usage: 43.2 MB, less than 8.33% of C++ online submissions for Maximum Sum Circular Subarray.
//time: O(n), space: O(n)
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int n = A.size();
        
        //kanade's algorithm
        int localMax = INT_MIN, globalMax = INT_MIN;
        
        for(int i = 0; i < n; i++){
            localMax = max(localMax, 0) + A[i];
            globalMax = max(globalMax, localMax);
        }
        
        //now consider 2-interval subarrays
        vector<int> rightsums(n);
        
        rightsums[n-1] = A[n-1];
        for(int i = n-2; i >= 0; i--){
            rightsums[i] = rightsums[i+1] + A[i];
        }
        
        //max rightsum starts at >= i
        vector<int> maxrights(n, 0);
        
        for(int i = n-1; i >= 0; i--){
            maxrights[i] = max((i+1 >= n ? INT_MIN : maxrights[i+1]), rightsums[i]);
        }
        
        /*
        leftsum: [0...i]
        maxrights[i+2]: max of rightsum starts from i+2
        start from i+2 to ensure this is a 2-interval subarray
        */
        int leftsum = 0;
        for(int i = 0; i+2 < n; i++){
            leftsum += A[i];
            globalMax = max(globalMax, leftsum + maxrights[i+2]);
        }
        
        return globalMax;
    }
};

//Approach 2: Prefix Sums + Monoqueue(deque)
//Runtime: 204 ms, faster than 6.83% of C++ online submissions for Maximum Sum Circular Subarray.
//Memory Usage: 44.9 MB, less than 8.33% of C++ online submissions for Maximum Sum Circular Subarray.
//time: O(n), space: O(n)
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int n = A.size();
        
        /*
        image an array B = A + A,
        P[i] is the prefix sum of B: ends at i-1,
        so P[0] is 0, P[1] is A[0], ...
        */
        vector<int> P(2*n+1, 0);
        for(int i = 0; i < 2*n; i++){
            P[i+1] = P[i] + A[i%n];
        }
        
        int ans = A[0];
        deque<int> dq;
        dq.push_back(0);
        
        //ends at j, exclusive
        for(int j = 1; j <= 2*n; j++){
            //subarray starts at dq.front()
            if(j-dq.front() > n){
                //if subarray's length > N, ignore this candidate
                dq.pop_front();
            }
            
            ans = max(ans, P[j] - P[dq.front()]);
            
            while(!dq.empty() && P[j] <= P[dq.back()]){
                /*
                j is the better starting point then dq.back(),
                because P[j] is smaller, so P[later_j] - P[starting point]
                can be larger
                */
                dq.pop_back();
            }
            
            //push candidate starting index
            dq.push_back(j);
        }
        
        return ans;
    }
};
