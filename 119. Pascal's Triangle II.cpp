//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Pascal's Triangle II.
//Memory Usage: 8.6 MB, less than 30.81% of C++ online submissions for Pascal's Triangle II.

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<vector<int>> pascal = {{1},
                                      {1,1}};
        
        for(int i = 2; i <= rowIndex; i++){
            //the length of ith row is i+1
            vector<int> row(i+1, 1);
            
            for(int j = 1; j < i+1-1; j++){
                row[j] = pascal[i-1][j-1] + pascal[i-1][j];
            }
            
            pascal.push_back(row);
        }
        
        return pascal[rowIndex];
    }
};

//solution from discusion

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Pascal's Triangle II.
//Memory Usage: 8.5 MB, less than 62.09% of C++ online submissions for Pascal's Triangle II.

/**
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> ans(rowIndex+1);
        ans[0] = 1;
        
        for(int i = 1; i < rowIndex + 1; i++){
            for(int j = i; j >= 1; j--){
                ans[j] += ans[j-1];
            }
        }
        return ans;
    }
};
**/
