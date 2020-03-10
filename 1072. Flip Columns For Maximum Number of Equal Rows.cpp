//TLE

class Solution {
public:
    bool all0(vector<int>& arr){
        return accumulate(arr.begin(), arr.end(), 0) == 0;
    };
    
    bool all1(vector<int>& arr){
        return accumulate(arr.begin(), arr.end(), 1, multiplies<int>()) == 1;
    };
    
    bool allSame(vector<int>& arr1, vector<int>& arr2){
        bool flag = true;
        for(int i = 0; i < arr1.size(); i++){
            if(arr1[i] != arr2[i]){
                flag = false;
                break;
            }
        }
        return flag;
    };
    
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> sum(n), reverted(n), ones(n, 1);
        int ans = 0;
        
        for(int i = 0; i < m; i++){
            set<vector<int>> group;
            int row_friend = 0;
            for(int j = 0; j < m; j++){
                if(j == i) continue;
                //sum two vector element-wise
                transform(matrix[i].begin(), matrix[i].end(),
                    matrix[j].begin(), sum.begin(), plus<int>());
                //if their sum is all 0 or all 1, 
                //row_friend++
                if(allSame(matrix[i], matrix[j]) || all1(sum)){
                // if(all1(sum)){
                    //ensure the 0th element is 0 and then record it into the set
                    reverted = matrix[i];
                    if(matrix[i][0] != 0){
                        transform(ones.begin(), ones.end(), matrix[i].begin(), reverted.begin(), minus<int>());
                    }
                    if(group.find(reverted) == group.end()){
                        row_friend += 2;
                    }else{
                        row_friend++;
                    }
                    group.insert(reverted);
                }
            }
            ans = max(ans, row_friend);
        }
        
        if(ans == 0){
            for(int i = 0; i < m; i++){
                if(all0(matrix[i]) || all1(matrix[i])){
                // if(all1(matrix[i])){
                    ans++;
                }
            }
        }
        
        //we can always do custom operations for a specific row
        if(ans == 0) ans = 1;
        
        return ans;
    }
};

//https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/discuss/303897/Java-easy-solution-%2B-explanation
//Runtime: 1620 ms, faster than 5.34% of C++ online submissions for Flip Columns For Maximum Number of Equal Rows.
//Memory Usage: 26.7 MB, less than 100.00% of C++ online submissions for Flip Columns For Maximum Number of Equal Rows.
class Solution {
public:
    bool all1(vector<int>& arr){
        return accumulate(arr.begin(), arr.end(), 1, multiplies<int>()) == 1;
    };
    
    bool allSame(vector<int>& a, vector<int>& b){
        bool flag = true;
        for(int i = 0; i < a.size(); i++){
            if(a[i] != b[i]){
                flag = false;
                break;
            }
        }
        return flag;
    };
    
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        int ans = 0;
        vector<int> sum(n);
        vector<int> reversed(n);
        
        for(int i = 0; i < m; i++){
            int row_friend = 0;
            for(int j = 0; j < m; j++){
                // transform(matrix[i].begin(), matrix[i].end(), matrix[j].begin(), sum.begin(), plus<int>());
                for(int k = 0; k < n; k++){
                    reversed[k] = 1 - matrix[j][k];
                }
                // if(allSame(matrix[i], matrix[j]) || all1(sum)){
                // if(allSame(matrix[i], matrix[j]) || allSame(matrix[i], reversed)){
                if(matrix[i] == matrix[j] || matrix[i] == reversed){
                    row_friend++;
                }
            }
            //row_friend's minimum is 1
            ans = max(ans, row_friend);
        }
        
        return ans;
    }
};

//speed the solution above with a set
//Runtime: 632 ms, faster than 9.71% of C++ online submissions for Flip Columns For Maximum Number of Equal Rows.
//Memory Usage: 27.4 MB, less than 100.00% of C++ online submissions for Flip Columns For Maximum Number of Equal Rows.
class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        int ans = 0;
        vector<int> sum(n);
        vector<int> reversed(n);
        set<int> grouped;
        
        for(int i = 0; i < m; i++){
            int row_friend = 0;
            //skip rows that can be grouped to earlier rows
            if(grouped.find(i) != grouped.end()) continue;
            for(int j = 0; j < m; j++){
                for(int k = 0; k < n; k++){
                    reversed[k] = 1 - matrix[j][k];
                }
                if(matrix[i] == matrix[j] || matrix[i] == reversed){
                    row_friend++;
                    grouped.insert(i);
                    grouped.insert(j);
                }
            }
            //row_friend's minimum is 1
            ans = max(ans, row_friend);
        }
        
        return ans;
    }
};
