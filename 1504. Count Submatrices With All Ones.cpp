//TLE
//67 / 72 test cases passed.
//time: O(m^2 * n^2)
class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size();
        if(m == 0) return 0;
        int n = mat[0].size();
        if(n == 0) return 0;
        
        /*
        padding a row and a column ahead
        so submatrixSum[i][j] corresponds to matrix[i-1][j-1]
        */
        vector<vector<int>> sms(m+1, vector(n+1, 0)); //submatrixSum
        
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                /*
                submatrix down to prev row + submatrix right to prev column - submatrix to its left-top
                plus
                current element
                */
                sms[i][j] += sms[i-1][j] + sms[i][j-1] - sms[i-1][j-1] + mat[i-1][j-1];
                // cout << sms[i][j] << " ";
            }
            // cout << endl;
        }
        
        int ans = 0;
        
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                //the length of the edge of the square
                for(int li = 1; li <= i; li++){
                    for(int lj = 1; lj <= j; lj++){
                        /*
                        use sms[i][j] - sms[i-len][j] - sms[i][j-len] + sms[i-len][j-len] to
                        calculate the sum of matrix[i-len...i-1, j-len...j-1]
                        */
                        if(sms[i][j] - sms[i-li][j] - sms[i][j-lj] + sms[i-li][j-lj] == li * lj){
                            // cout << "(" << i << ", " << j << "), length: " << len << endl;
                            ans++;
                        }
                    }
                }
            }
        }
        
        return ans;
    }
};

//compress submatrix into an array
//https://leetcode.com/problems/count-submatrices-with-all-ones/discuss/720265/Java-Detailed-Explanation-From-O(MNM)-to-O(MN)-by-using-Stack
//Runtime: 132 ms, faster than 39.02% of C++ online submissions for Count Submatrices With All Ones.
//Memory Usage: 14.2 MB, less than 100.00% of C++ online submissions for Count Submatrices With All Ones.
//time: O(m^2 * n)
class Solution {
public:
    int numSubarr(vector<int>& arr){
        int n = arr.size();
        
        int len = 0, count = 0;
        
        for(int i = 0; i < n; ++i){
            /*
            len: the count of all one subarray
            ending at "i"
            */
            len = (arr[i] == 0) ? 0 : len+1;
            /*
            count is the sum of subarrays
            ending at i=0~n-1
            */
            count += len;
        }
        
        return count;
    };
    
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size();
        if(m == 0) return 0;
        int n = mat[0].size();
        if(n == 0) return 0;
        
        int count = 0;
        
        for(int up = 0; up < m; ++up){
            /*
            h is the compressed matrix mat[up~down, 0~n-1]
            */
            vector<int> h(n, 1);
            for(int down = up; down < m; ++down){
                /*
                extend the submatrix by adding the row "down"
                and add its info into the compressed matrix "h"
                */
                for(int i = 0; i < n; ++i){
                    h[i] &= mat[down][i];
                }
                /*
                sum of submatrices (up, down) = (0,0) to (m-1, m-1)
                */
                count += numSubarr(h);
                // cout << "[" << up << ", " << down << "]: " << numSubarr(h) << endl;
            }
        }
        
        return count;
    }
};

