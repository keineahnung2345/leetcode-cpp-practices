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
