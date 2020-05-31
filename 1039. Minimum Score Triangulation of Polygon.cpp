//recursion
//TLE
//73 / 93 test cases passed.
class Solution {
public:
    int minScoreTriangulation(vector<int>& A, int i, int j) {
        // if(j == 0) j = A.size()-1;
        
        //we cannot find a k between i and j
        if(j - i < 2) return 0;
        
        int res = INT_MAX;
        
        for(int k = i+1; k <= j-1; k++){
            // cout << i << ", " << k << ", " << j << endl;
            res = min(res,
                minScoreTriangulation(A, i, k) + A[i]*A[k]*A[j] +
                minScoreTriangulation(A, k, j));
        }
        
        return res;
    }
    
    int minScoreTriangulation(vector<int>& A) {
        int n = A.size();
        return minScoreTriangulation(A, 0, n-1);
    }
};

//recursion + memo
//https://leetcode.com/problems/minimum-score-triangulation-of-polygon/discuss/286753/C%2B%2B-with-picture
//Runtime: 12 ms, faster than 28.53% of C++ online submissions for Minimum Score Triangulation of Polygon.
//Memory Usage: 8.7 MB, less than 100.00% of C++ online submissions for Minimum Score Triangulation of Polygon.
class Solution {
public:
    vector<vector<int>> memo;
    
    int minScoreTriangulation(vector<int>& A, int i, int j) {
        //we cannot find a k between i and j
        if(j - i < 2) return 0;
        
        if(memo[i][j] != INT_MAX){
            return memo[i][j];
        }
        
        for(int k = i+1; k <= j-1; k++){
            // cout << i << ", " << k << ", " << j << endl;
            memo[i][j] = min(memo[i][j],
                minScoreTriangulation(A, i, k) + A[i]*A[k]*A[j] +
                minScoreTriangulation(A, k, j));
        }
        
        return memo[i][j];
    }
    
    int minScoreTriangulation(vector<int>& A) {
        int n = A.size();
        memo = vector<vector<int>>(n, vector<int>(n, INT_MAX));
        return minScoreTriangulation(A, 0, n-1);
    }
};
