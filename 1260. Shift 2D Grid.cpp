//Runtime: 88 ms, faster than 23.45% of C++ online submissions for Shift 2D Grid.
//Memory Usage: 14.4 MB, less than 100.00% of C++ online submissions for Shift 2D Grid.
class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<pair<int, int>>> pos(m, vector<pair<int, int>>(n));
        vector<vector<int>> ans(m, vector<int>(n));
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                pos[i][j] = make_pair(i, j);
            }
        }
        
        //calculate each index is shifted to where
        for(int time = 0; time < k; time++){
            // cout << "time: " << time << endl;
            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    // cout << pos[i][j].first << ", " << pos[i][j].second << endl;
                    if(pos[i][j].second < n-1){
                        //(i,j)->(i,j+1)
                        pos[i][j].second += 1;
                    }else if(pos[i][j].first < m-1){
                        //(i,n-1)->(i+1,0)
                        pos[i][j] = make_pair(pos[i][j].first+1, 0);
                    }else{
                        //(m-1,n-1) -> (0,0)
                        pos[i][j] = make_pair(0,0);
                    }
                }
            }
        }
        
        //(pos[i][j].first, pos[i][j].second): new position of original (i,j)
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                //(i, j) now move to (pos[i][j].first, pos[i][j].second)
                ans[pos[i][j].first][pos[i][j].second] = grid[i][j];
            }
        }
        
        return ans;
    }
};

//Approach 3: Using Modulo Arithmetic
//time: O(m*n), space: O(m*n)
//Runtime: 68 ms, faster than 75.78% of C++ online submissions for Shift 2D Grid.
//Memory Usage: 13.4 MB, less than 100.00% of C++ online submissions for Shift 2D Grid.
class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> ans(m, vector<int>(n, 0));
        
        for(int i = 0 ; i < m; i++){
            for(int j = 0; j < n; j++){
                int new_j = (j + k)%n;
                int new_i = (i + (j + k)/n)%m;
                ans[new_i][new_j] = grid[i][j];
            }
        }
        
        return ans;
    }
};
