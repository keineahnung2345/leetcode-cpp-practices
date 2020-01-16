//Runtime: 132 ms, faster than 71.89% of C++ online submissions for XOR Queries of a Subarray.
//Memory Usage: 26.2 MB, less than 100.00% of C++ online submissions for XOR Queries of a Subarray.

class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        vector<int> dp = arr;
        vector<int> results;
        int l, r;
        
        for(int i = 1; i < dp.size(); i++){
            dp[i] ^= dp[i-1];
        }
        
        for(vector<int>& query : queries){
            l = query[0]; r = query[1];
            int result = dp[r];
            if(l > 0){
                //doing XOR twice equals doing nothing
                result ^= dp[l-1];
            }
            results.push_back(result);
        }
        
        return results;
    }
};
