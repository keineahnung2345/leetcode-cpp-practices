//DP, greedy
//WA
//47 / 56 test cases passed.
/*
two pass(forward and backward),
in each pass, greedily maximize the profit it gets,
but this doesn't work for the case:
[[1,1,1,1,0,0,0],
[0,0,0,1,0,0,0],
[0,0,0,1,0,0,1],
[1,0,0,1,0,0,0],
[0,0,0,1,0,0,0],
[0,0,0,1,0,0,0],
[0,0,0,1,1,1,1]]
where in the first pass, 
we shouldn't choose the path that will maximize the profit!
*/
//time: O(N^2), space: O(N^2)
enum class DIR{
    NONE = 0,
    UP = 1,
    LEFT = 2
};

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        
        if(n == 1) return max(grid[0][0], 0);
        
        vector<vector<int>> dpf(n, vector<int>(n, 0));
        vector<vector<int>> dpb(n, vector<int>(n, 0));
        vector<vector<DIR>> from(n, vector<DIR>(n, DIR::NONE));
        
        //base case
        dpf[0][0] = grid[0][0];
        grid[0][0] = 0;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(grid[i][j] == -1){
                    dpf[i][j] = -1;
                }else{
                    if(i-1 >= 0 && dpf[i-1][j] != -1){
                        if(dpf[i-1][j]+grid[i][j] > dpf[i][j]){
                            dpf[i][j] = dpf[i-1][j]+grid[i][j];
                            from[i][j] = DIR::UP;
                        }
                    }
                    if(j-1 >= 0 && dpf[i][j-1] != -1){
                        if(dpf[i][j-1]+grid[i][j] > dpf[i][j]){
                            dpf[i][j] = dpf[i][j-1]+grid[i][j];
                            from[i][j] = DIR::LEFT;
                        }
                    }
                }
            }
        }
        
        // cout << "dpf: " << endl;
        // for(int i = 0; i < n; ++i){
        //     for(int j = 0; j < n; ++j){
        //         cout << dpf[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        
        // cout << "from: " << endl;
        // for(int i = 0; i < n; ++i){
        //     for(int j = 0; j < n; ++j){
        //         if(from[i][j] == DIR::NONE) cout << 0;
        //         else if(from[i][j] == DIR::LEFT) cout << 1;
        //         else cout << 2;
        //         cout << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        
        //go backward the path and update "grid"
        // cout << "go backward: " << endl;
        int i = n-1, j = n-1;
        while(i != 0 || j != 0){
            // cout << "(" << i << ", " << j << ")" << endl;
            if(grid[i][j] > 0) grid[i][j] = 0;
            
            //go to previous position
            if(from[i][j] == DIR::LEFT){
                --j;
            }else if(from[i][j] == DIR::UP){
                --i;
            }else{
                //no way to go back!
                return 0;
            }
        }
        
        // cout << "grid: " << endl;
        // for(int i = 0; i < n; ++i){
        //     for(int j = 0; j < n; ++j){
        //         cout << grid[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        
        for(int i = n-1; i >= 0; --i){
            for(int j = n-1; j >= 0; --j){
                if(dpf[i][j] == -1){
                    dpb[i][j] = -1;
                }else{
                    if(i+1 < n && dpb[i+1][j] != -1){
                        dpb[i][j] = max(dpb[i+1][j]+grid[i][j], dpb[i][j]);
                    }
                    if(j+1 < n && dpb[i][j+1] != -1){
                        dpb[i][j] = max(dpb[i][j+1]+grid[i][j], dpb[i][j]);
                    }
                }
            }
        }
        
        // cout << "dpb: " << endl;
        // for(int i = 0; i < n; ++i){
        //     for(int j = 0; j < n; ++j){
        //         cout << dpb[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        
        return dpf[n-1][n-1] + dpb[0][0];
    }
};

//Approach #2: Dynamic Programming (Top Down)
//two players go from (0,0) to (N-1,N-1)
//Runtime: 76 ms, faster than 56.33% of C++ online submissions for Cherry Pickup.
//Memory Usage: 22.6 MB, less than 56.16% of C++ online submissions for Cherry Pickup.
//time: O(N^3), space: O(N^3)
class Solution {
public:
    int n;
    vector<vector<vector<int>>> memo;
    
    int dfs(vector<vector<int>>& grid, int r1, int c1, int r2){
        //r1+r2 = c1+c2 -> c2 = r1+r2-c1
        int c2 = r1+c1-r2;
        //out of boundary
        if(r1 >= n || c1 >= n || r2 >= n || c2 >= n){
            return INT_MIN;
        }
        //cannot go to this cell
        if(grid[r1][c1] == -1 || grid[r2][c2] == -1){
            return INT_MIN;
        }
        //stop condition
        if(r1 == n-1 && c1 == n-1){
            //r2 and c2 will also be n-1, too!
            return grid[n-1][n-1];
        }
        if(memo[r1][c1][r2] != INT_MIN){
            return memo[r1][c1][r2];
        }
        
        int ans;
        
        ans = grid[r1][c1];
        //avoid add the same grid twice
        if(r1 != r2) ans += grid[r2][c2];
        ans += max({dfs(grid, r1+1, c1, r2+1), //p1, p2: down
                    dfs(grid, r1, c1+1, r2), //p1, p2: right, new_c2=r1+c1+1-r2=old_c2+1
                    dfs(grid, r1+1, c1, r2), //p1: down, p2: right, new_c2=old_c2+1=r1+c1-r2+1=r1+1+c1-new_r2
                    dfs(grid, r1, c1+1, r2+1)}); //p1: right, p2: down
        
        return memo[r1][c1][r2] = ans;
    };
    
    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        
        memo = vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>(n, INT_MIN)));
        
        /*
        if the return value is negative, 
        that means the path is invalid, 
        so no cherry to pick, 
        giving us profit = 0
        */
        return max(0, dfs(grid, 0, 0, 0));
    }
};
