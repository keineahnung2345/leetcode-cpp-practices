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

//dfs + binary search
//https://leetcode.com/problems/swim-in-rising-water/discuss/113758/C%2B%2B-two-solutions-Binary-Search%2BDFS-and-Dijkstra%2BBFS-O(n2logn)-11ms
//Runtime: 32 ms, faster than 76.63% of C++ online submissions for Swim in Rising Water.
//Memory Usage: 10.1 MB, less than 50.00% of C++ online submissions for Swim in Rising Water.
class Solution {
    bool validPos(int i, int j, int n){
        return i >= 0 && i < n && j >= 0 && j < n;
    };
    
    bool dfs(vector<vector<int>>& grid, vector<vector<int>>& dirs, vector<vector<bool>>& visited, int t, int i, int j){
        int n = grid.size();
        for(vector<int>& dir : dirs){
            int ni = i+dir[0];
            int nj = j+dir[1];
            if(validPos(ni, nj, n) && !visited[ni][nj] && grid[ni][nj] <= t){
                visited[ni][nj] = true;
                if(ni == n-1 && nj == n-1) return true;
                if(dfs(grid, dirs, visited, t, ni, nj)) return true;
            }
        }
        return false;
    };
    
    bool valid(vector<vector<int>>& grid, int t){
        int n = grid.size();
        vector<vector<bool>> visited(n, vector(n, false));
        visited[0][0] = true;
        vector<vector<int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
        return dfs(grid, dirs, visited, t, 0, 0);
    };
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        
        int left = max(grid[0][0], grid[n-1][n-1]);
        int right = n*n-1; //grid is a permutation of [0,...,n*n-1]
        int mid;
        
        while(left <= right){
            mid = left + (right-left)/2;
            if(valid(grid, mid)){
                right = mid-1;
            }else{
                left = mid+1;
            }
        }
        
        return left;
    }
};

//Dijkstra using Priority Queue
//https://leetcode.com/problems/swim-in-rising-water/discuss/113758/C%2B%2B-two-solutions-Binary-Search%2BDFS-and-Dijkstra%2BBFS-O(n2logn)-11ms
//Runtime: 108 ms, faster than 16.72% of C++ online submissions for Swim in Rising Water.
//Memory Usage: 11.3 MB, less than 25.00% of C++ online submissions for Swim in Rising Water.
//time: O(N^2logN), space: O(N^2)
class Solution {
    bool validPos(int i, int j, int n){
        return i >= 0 && i < n && j >= 0 && j < n;
    };
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        
        vector<vector<bool>> visited(n, vector(n, false));
        
        vector<vector<int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
        //the smaller the earlier be popped
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        
        pq.push({grid[0][0], 0, 0});
        visited[0][0] = true;
        
        int ans = max(grid[0][0], grid[n-1][n-1]);
        
        //visit node in increasing height order
        while(!pq.empty()){
            vector<int> node = pq.top(); pq.pop();
            int i = node[1], j = node[2];
            //update ans when we actually visit the node
            ans = max(ans, node[0]);
            // visited[i][j] = true;
            for(vector<int>& dir : dirs){
                int ni = i+dir[0];
                int nj = j+dir[1];
                if(validPos(ni, nj, n) && !visited[ni][nj]){
                    if(ni == n-1 && nj == n-1) return ans;
                    //here mark neighbor as visited just to avoid it be added to pq again
                    visited[ni][nj] = true;
                    pq.push({grid[ni][nj], ni, nj});
                }
            }
        }
        
        return ans;
    }
};

