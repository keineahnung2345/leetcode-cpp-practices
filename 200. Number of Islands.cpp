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

//Union Find
//Runtime: 24 ms, faster than 16.98% of C++ online submissions for Number of Islands.
//Memory Usage: 9.1 MB, less than 100.00% of C++ online submissions for Number of Islands.
class DSU{
public:
    vector<int> parent;
    
    DSU(int n){
        parent= vector<int>(n);
        iota(parent.begin(), parent.end(), 0);
    };
    
    int find(int x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };
    
    void unite(int x, int y){
        // parent[x] = find(parent[y]);
        // parent[y] = find(parent[x]);
        parent[find(x)] = find(y);
    };
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        if(m == 0) return 0;
        int n = grid[0].size();
        
        vector<vector<int>> dirs = {
            {1,0},
            {-1,0},
            {0,1},
            {0,-1}
        };
        
        DSU dsu(m*n);
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                // cout << "cur: " << i << " " << j << endl;
                if(grid[i][j] != '1') continue;
                for(vector<int>& dir : dirs){
                    int newI = i + dir[0];
                    int newJ = j + dir[1];
                    if(newI >= 0 && newI < m && newJ >= 0 && newJ < n && grid[newI][newJ] == '1'){
                        // cout << newI << " " << newJ << endl;
                        dsu.unite(i*n+j, newI*n+newJ);
                        // cout << "(" << i << ", " << j << ", " << dsu.parent[i*n+j] << "), (" << newI << ", " << newJ << ", " << dsu.parent[newI*n+newJ] << ")" << endl;
                    }
                    
                }
            }
        }
        
        set<int> uniqParent;
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == '1'){
                    // cout << i << " " << j << " " <<　dsu.find(i*n+j) << endl;
                    uniqParent.insert(dsu.find(i*n+j));
                }
            }
        }
        
        return uniqParent.size();
    }
};
