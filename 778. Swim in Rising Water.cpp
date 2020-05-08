//bfs + binary search
//Runtime: 1020 ms, faster than 5.16% of C++ online submissions for Swim in Rising Water.
//Memory Usage: 63.2 MB, less than 5.00% of C++ online submissions for Swim in Rising Water.
class Solution {
public:
    bool validPos(int i, int j, int m, int n){
        return i >= 0 && i < m && j >= 0 && j < m;
    };
    
    bool connect(vector<vector<int>>& grid, int t){
        // cout << "time: " << t << endl;
        queue<vector<int>> q;
        set<vector<int>> connected;
        
        int m = grid.size(), n = grid[0].size();
        q.push(vector<int>{0,0});
        connected.insert({0,0});
        
        vector<vector<int>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        
        int count = 0;
        //bfs
        while(!q.empty()){
            vector<int> node = q.front(); q.pop();
            
            for(vector<int>& dir : dirs){
                int ni = node[0]+dir[0], nj = node[1]+dir[1];
                vector<int> nbr = {ni, nj};
                //not valid position
                if(!validPos(ni, nj, m, n)) continue;
                //already visited
                if(connected.find(nbr) != connected.end()) continue;
                //water is over nbr
                if(grid[ni][nj] <= t){
                    // cout << "(" << ni << ", " << nj << "): " << grid[ni][nj] << " | ";
                    q.push({ni, nj});
                    if(nbr[0] == m-1 && nbr[1] == n-1){
                        // cout << endl;
                        return true;
                    }
                    connected.insert(nbr);
                }
            }
            
            count++;
        }
        // cout << endl;
        return false;
    };
    
    int swimInWater(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        int right = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                right = max(right, grid[i][j]);
            }
        }
        
        int left = max(grid[0][0], grid[m-1][n-1]);
        int mid;
        
        //binary search, find left boundary
        while(left <= right){
            mid = left + (right-left)/2;
            if(connect(grid, mid)){
                right = mid-1;
            }else{
                left = mid+1;
            }
        }
        // cout << endl;
        if(left == m*n) return -1;
        return left;
    }
};
