//Runtime: 44 ms, faster than 7.77% of C++ online submissions for Number of Islands.
//Memory Usage: 12.2 MB, less than 12.36% of C++ online submissions for Number of Islands.
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        if(m == 0) return 0;
        int n = grid[0].size();
        
        queue<vector<int>> q;
        int i = 0;
        vector<vector<int>> dirs = {
            {1,0},
            {-1,0},
            {0,1},
            {0,-1}
        };
        vector<vector<bool>> visited(m, vector(n, false));
        int ans = 0;
        
        while(i < m*n){
            while(i < m*n && !(!visited[i/n][i%n] && grid[i/n][i%n] == '1')){
                i++;
            }
            if(i >= m*n) break;
            // cout << i/n << " " << i%n << endl;
            
            visited[i/n][i%n] = true;
            q.push({i/n, i%n});
            ans++;

            //visite all cell connected to it
            while(!q.empty()){
                vector<int> cur = q.front(); q.pop();
                int curI = cur[0], curJ = cur[1];

                // cout << "cur: " << curI << " " << curJ << endl;

                for(vector<int>& dir : dirs){
                    int newI = curI + dir[0];
                    int newJ = curJ + dir[1];
                    if(newI >= 0 && newI < m && newJ >= 0 && newJ < n && !visited[newI][newJ] && grid[newI][newJ] == '1'){
                        visited[newI][newJ] = true;
                        q.push({newI, newJ});
                    }
                }
            }
        }
        
        // cout << endl << endl;
        
        return ans;
    }
};
