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

//monotonic stack
//Runtime: 76 ms, faster than 89.47% of C++ online submissions for Count Submatrices With All Ones.
//Memory Usage: 16.3 MB, less than 100.00% of C++ online submissions for Count Submatrices With All Ones.
//https://leetcode.com/problems/count-submatrices-with-all-ones/discuss/720265/Java-Detailed-Explanation-From-O(MNM)-to-O(MN)-by-using-Stack
//time: O(m*n)
class Solution {
public:
    int helper(vector<int>& h){
        /*
        counts[j]: count of submatrix ending at column j
        */
        vector<int> counts(h.size());
        /*
        monotonic stack,
        top element is the largest
        */
        stack<int> stk;
        
        for(int j = 0; j < h.size(); ++j){
            /*
            we want to find the former nearset column
            which is lower
            */
            while(!stk.empty() && h[stk.top()] >= h[j]){
                stk.pop();
            }
            
            if(!stk.empty()){
                int preIndex = stk.top();
                /*
                valid height range: [1,h[j]]
                valid width range:［preIndex+1,j]
             	
             	add count of submatrices ending at 
             	column preIndex: counts[preIndex]??
                */
                /*
                why not adding the submatrices formed by
                even former, even shorter columns??
                */
                counts[j] = h[j] * (j - preIndex) + counts[preIndex];
            }else{
                /*
                all previous columns' are 
                at least taller as current column,
                so the submatrices can start at one of [0,j]
                
                valid height range: [1,h[j]]
                valid width range: [0,j]
                
                so total we could have h[j] * (j+1) submatrices
                ending at j
                */
                counts[j] = h[j] * (j+1);
            }
            
            /*
            current index j is pushed into stack,
            it's used later as previous index
            */
            stk.push(j);
        }
        
        return accumulate(counts.begin(), counts.end(), 0);
    };
    
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size();
        if(m == 0) return 0;
        int n = mat[0].size();
        if(n == 0) return 0;
        
        int count = 0;
        
        vector<int> h(n, 0);
        for(int i = 0; i < m; ++i){
            //construct h
            for(int j = 0; j < n; ++j){
                /*
                h[j]: height of continuous ones in column j,
                its bottom is row i
                */
                h[j] = (mat[i][j] == 0) ? 0 : h[j]+1;
            }
            count += helper(h);
        }
        
        return count;
    }
};
