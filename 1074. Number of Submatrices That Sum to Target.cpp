//DP
//TLE
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int ans = 0;
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                int left = (j-1) >= 0 ? dp[i][j-1] : 0;
                int top = (i-1) >= 0 ? dp[i-1][j] : 0;
                int lefttop = ((i-1) >= 0 && (j-1) >= 0) ? dp[i-1][j-1] : 0;
                dp[i][j] = matrix[i][j] + left + top - lefttop;
            }
        }
        
        //coords acts as helper to generate the range of submatrix
        // vector<pair<int, int>> coords;
        vector<pair<int, int>> coords((1+max(m,n))*(max(m,n))/2);
        
        int tmp = 0;
        for(int high = 0; high < max(m, n); high++){
            for(int low = 0; low <= high; low++){
                coords[tmp++] = make_pair(low, high);
                // cout << low << "-" << high << endl;
            }
        }
        
        int mtri = (1+m)*m/2, ntri = (1+n)*n/2;
        
        // cout << "mtri: " << mtri << ", ntri: " << ntri << endl;
        
        
        //generate submatrices and check their sum
        for(int i = 0; i < mtri; i++){
            for(int j = 0; j < ntri; j++){
                int ilow = coords[i].first, ihigh = coords[i].second;
                int jlow = coords[j].first, jhigh = coords[j].second;
                // cout << "(" << i << "," << j << "): " << "[" << ilow << "," << ihigh << "] - [" << jlow << "," << jhigh << "]" << endl;
                int left = (jlow-1) >= 0 ? dp[ihigh][jlow-1] : 0;
                int top = (ilow-1) >= 0 ? dp[ilow-1][jhigh] : 0;
                int lefttop = ((ilow-1) >= 0 && (jlow-1) >= 0) ? dp[ilow-1][jlow-1] : 0;
                int submatrix = dp[ihigh][jhigh] - left - top + lefttop;
                if(submatrix == target){
                    ans++;
                }
            }
        }
        
        return ans;
    }
};

//https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/discuss/303750/JavaC%2B%2BPython-Find-the-Subarray-with-Target-Sum
//time: O(N^3), space: O(N)
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int ans = 0, m = matrix.size(), n = matrix[0].size();
        
        //convert A to prefix sum of each row
        for(int i = 0; i < m; i++){
            for(int j = 1; j < n; j++){
                matrix[i][j] += matrix[i][j-1];
            }
        }
        
        for(int col_low = 0; col_low < n; col_low++){
            for(int col_high = col_low; col_high < n; col_high++){
                unordered_map<int, int> counter;
                counter[0] = 1;
                int cur = 0;
                for(int row = 0; row < m; row++){
                    cur += matrix[row][col_high] - ((col_low > 0) ? matrix[row][col_low-1] : 0);
                    ans += counter[cur - target];
                    // cout << row << ", [" << col_low << ", " << col_high << " ]" << ", cur: " << cur << ", ans: " << ans << endl;
                    counter[cur]++;
                }
            }
        }
        
        return ans;
    }
};

//Treat submatrix as subarray and use sliding window
//https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/discuss/303773/C%2B%2B-O(n3)-Simple-1D-Subarray-target-sum-applied-to-2D-array
//Runtime: 5772 ms, faster than 59.72% of C++ online submissions for Number of Submatrices That Sum to Target.
//Memory Usage: 455.5 MB, less than 100.00% of C++ online submissions for Number of Submatrices That Sum to Target.
class Solution {
public:
    int subarraySum(vector<int>& arr, int target){
        int res = 0, sum = 0;
        map<int, int> counter;
        counter[0] = 1;
        for(int i = 0; i < arr.size(); i++){
            sum += arr[i];
            if(counter.find(sum - target) != counter.end()){
                res += counter[sum - target];
            }
            counter[sum]++;
        }
        return res;
    };
    
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int ans = 0;
        vector<int> row(n);
        
        for(int row_low = 0; row_low < m; row_low++){
            //cumulative sum start from row_low
            fill(row.begin(), row.end(), 0);
            for(int row_high = row_low; row_high < m; row_high++){
                //cumulative sum until row_high
                for(int col = 0; col < n; col++){
                    row[col] += matrix[row_high][col];
                }
                //think the submatrix as an array
                //and then find its subarray's sum
                ans += subarraySum(row, target);
            }
        }
        
        return ans;
    }
};
