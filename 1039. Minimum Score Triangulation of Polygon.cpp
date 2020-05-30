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
