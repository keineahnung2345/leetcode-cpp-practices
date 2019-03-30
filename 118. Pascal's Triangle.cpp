/**
Given a non-negative integer numRows, generate the first numRows of Pascal's triangle.


In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:

Input: 5
Output:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
**/

/**
Approach 1: Dynamic Programming
**/

/**
Complexity Analysis
Time complexity : O(numRows^2)
Space complexity : O(numRows^2)
**/

//Runtime: 8 ms, faster than 25.38% of C++ online submissions for Pascal's Triangle.
//Memory Usage: 8.7 MB, less than 86.38% of C++ online submissions for Pascal's Triangle.

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
        for(int i = 1; i <= numRows; i++){
            vector<int> v  = vector<int>(i, 1);
            if(i > 2){
                for(int j = 1; j <= v.size()-2; j++){
                    v[j] = ans[ans.size()-1][j-1] + ans[ans.size()-1][j];
                }
            }
            ans.push_back(v);
        }
        return ans;
    }
};
