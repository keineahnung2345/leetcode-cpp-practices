/**
On a N * N grid, we place some 1 * 1 * 1 cubes that are axis-aligned with the x, y, and z axes.

Each value v = grid[i][j] represents a tower of v cubes placed on top of grid cell (i, j).

Now we view the projection of these cubes onto the xy, yz, and zx planes.

A projection is like a shadow, that maps our 3 dimensional figure to a 2 dimensional plane. 

Here, we are viewing the "shadow" when looking at the cubes from the top, the front, and the side.

Return the total area of all three projections.

 

Example 1:

Input: [[2]]
Output: 5
Example 2:

Input: [[1,2],[3,4]]
Output: 17
Explanation: 
Here are the three projections ("shadows") of the shape made with each axis-aligned plane.

Example 3:

Input: [[1,0],[0,2]]
Output: 8
Example 4:

Input: [[1,1,1],[1,0,1],[1,1,1]]
Output: 14
Example 5:

Input: [[2,2,2],[2,1,2],[2,2,2]]
Output: 21
 

Note:

1 <= grid.length = grid[0].length <= 50
0 <= grid[i][j] <= 50
**/

//Your runtime beats 99.47 % of cpp submissions.
class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int xy = 0;
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[0].size(); j++){
                if(grid[i][j]>0) xy++;
            }
        }
        int xz = 0;
        for(int i = 0; i < grid.size(); i++){
            xz+= *max_element(grid[i].begin(), grid[i].end());
        }
        int yz = 0;
        for(int j = 0; j < grid[0].size(); j++){
            int col_max = 0;
            for(int i = 0; i < grid.size(); i++){
                col_max = max(col_max, grid[i][j]);
            }
            yz+=col_max;
        }
        // cout << xy << " " << xz << " " << yz << endl;
        return xy+xz+yz;
    }
};

/**
Approach 1: Mathematical
Intuition and Algorithm

From the top, the shadow made by the shape will be 1 square for each non-zero value.

From the side, the shadow made by the shape will be the largest value for each row in the grid.

From the front, the shadow made by the shape will be the largest value for each column in the grid.

Example

With the example [[1,2],[3,4]]:

The shadow from the top will be 4, since there are four non-zero values in the grid;

The shadow from the side will be 2 + 4, since the maximum value of the first row is 2, and the maximum value of the second row is 4;

The shadow from the front will be 3 + 4, since the maximum value of the first column is 3, and the maximum value of the second column is 4.
**/

//Your runtime beats 99.47 % of cpp submissions.
class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int ans = 0;
        int N = grid.size();
        for(int i = 0; i < N; i++){
            int rowBest = 0;
            int colBest = 0;
            for(int j = 0; j < N; j++){
                if(grid[i][j]>0) ans++;
                rowBest = max(rowBest, grid[i][j]);
                //since grid is a square, so we can do this
                colBest = max(colBest, grid[j][i]);
            }
            ans+=rowBest+colBest;
        }
        return ans;
    }
};

/**
Complexity Analysis

Time Complexity: O(N^2), where N is the length of grid.

Space Complexity: O(1). 
**/
