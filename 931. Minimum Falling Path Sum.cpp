//Recursion
//TLE

class Solution {
public:
    int N;
    
    int minFallingPathSumR(vector<vector<int>>& A, int row, int col) {
        
        //invalid index, ignore it
        if(col < 0 || col >= N) return INT_MAX;
        //stop the recursion
        if(row >= N) return 0;
        //last row
        if(row == N-1) return A[row][col];
        
        int x = A[row][col] + min({minFallingPathSumR(A, row+1, col-1), minFallingPathSumR(A, row+1, col), minFallingPathSumR(A, row+1, col+1)});
        
        // cout << row << " " << col << " " << x << endl;
        
        return x;
    };
    
    int minFallingPathSum(vector<vector<int>>& A) {
        N = A.size();
        vector<int> arr(N);
        
        for(int col = 0; col < N; col++){
            arr[col] = A[0][col] + min({minFallingPathSumR(A, 1, col-1), minFallingPathSumR(A, 1, col), minFallingPathSumR(A, 1, col+1)});
        }
        
        return *min_element(arr.begin(), arr.end());
    }
};

//dp
//Runtime: 28 ms, faster than 6.41% of C++ online submissions for Minimum Falling Path Sum.
//Memory Usage: 9.3 MB, less than 100.00% of C++ online submissions for Minimum Falling Path Sum.
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& A) {
        int N = A.size();
        vector<vector<int>> dp(N+2, vector<int>(N+2, INT_MAX));
        
        //dp: wrap A with a margin of width 1
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                dp[i+1][j+1] = A[i][j];
            }
        }
        
        //skip last row
        for(int row = N-1; row >= 1; row--){ //[0,N-2]+1
            for(int col = 1; col <= N; col++){ //[0,N-1]+1
                dp[row][col] += min({dp[row+1][col-1], dp[row+1][col], dp[row+1][col+1]});
            }
        }
        
        return *min_element(dp[1].begin(), dp[1].end());
    }
};
