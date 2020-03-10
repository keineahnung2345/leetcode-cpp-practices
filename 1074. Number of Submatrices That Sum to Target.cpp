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
