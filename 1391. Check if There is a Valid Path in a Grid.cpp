//Graph, BFS
//Runtime: 428 ms, faster than 27.27% of C++ online submissions for Check if There is a Valid Path in a Grid.
//Memory Usage: 72 MB, less than 100.00% of C++ online submissions for Check if There is a Valid Path in a Grid.
class Solution {
public:
    vector<vector<bool>> visited;
    vector<vector<int>> grid;
    vector<int> right;
    vector<int> left;
    vector<int> up;
    vector<int> down;
    int m, n;
    
    bool leftValid(int i, int j){
        if(j >= 0 && !visited[i][j] && find(right.begin(), right.end(), grid[i][j]) != right.end())
            return true;
        return false;
    };
    
    bool rightValid(int i, int j){
        if(j < n && !visited[i][j] && find(left.begin(), left.end(), grid[i][j]) != left.end())
            return true;
        return false;
    };
    
    bool upValid(int i, int j){
        if(i >= 0 && !visited[i][j] && find(down.begin(), down.end(), grid[i][j]) != down.end())
            return true;
        return false;
    };
    
    bool downValid(int i, int j){
        // cout << "downValid: " << i+1 << " " << j << 
        if(i < m && !visited[i][j] && find(up.begin(), up.end(), grid[i][j]) != up.end())
            return true;
        return false;
    };
    
    bool hasValidPath(vector<vector<int>>& grid) {
        this->grid = grid;
        this->m = grid.size();
        this->n = grid[0].size();
        visited = vector<vector<bool>>(this->m, vector<bool>(this->n, false));
        
        //can connect to which direction
        // int tmp[3] = {1,4,6};
        right = {1,4,6};
        // right.assign(&tmp[0], &tmp[0]+3);
        left = {1,3,5};
        up = {2,5,6};
        down = {2,3,4};
        
        queue<vector<int>> q;
        
        q.push({0,0});
        
        while(!q.empty()){
            vector<int> cur = q.front(); q.pop();
            int i = cur[0], j = cur[1];
            // cout << i << " " << j << endl;
            visited[i][j] = true;
            
            //we have reached the goal!
            if(i == m-1 && j == n-1) return true;
            
            switch(grid[i][j]){
                case 1:
                    //left
                    if(leftValid(i, j-1)){
                        q.push({i, j-1});
                    }
                    //right
                    if(rightValid(i, j+1)){
                        q.push({i, j+1});
                    }
                    break;
                case 2:
                    //up
                    if(upValid(i-1, j)){
                        q.push({i-1, j});
                    }
                    //down
                    if(downValid(i+1, j)){
                        q.push({i+1, j});
                    }
                    break;
                case 3:
                    //left
                    if(leftValid(i, j-1)){
                        q.push({i, j-1});
                    }
                    //down
                    if(downValid(i+1, j)){
                        q.push({i+1, j});
                    }
                    break;
                case 4:
                    //right
                    if(rightValid(i, j+1)){
                        q.push({i, j+1});
                    }
                    //down
                    if(downValid(i+1, j)){
                        q.push({i+1, j});
                    }
                    break;
                case 5:
                    //up
                    if(upValid(i-1, j)){
                        q.push({i-1, j});
                    }
                    //left
                    if(leftValid(i, j-1)){
                        q.push({i, j-1});
                    }
                    break;
                case 6:
                    //up
                    if(upValid(i-1, j)){
                        q.push({i-1, j});
                    }
                    //right
                    if(rightValid(i, j+1)){
                        q.push({i, j+1});
                    }
                    break;
            }
        }
        
        return false;
    }
};

//Graph, BFS
//https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/discuss/547371/Java-clean-BFS
//Runtime: 472 ms, faster than 18.18% of C++ online submissions for Check if There is a Valid Path in a Grid.
//Memory Usage: 66.3 MB, less than 100.00% of C++ online submissions for Check if There is a Valid Path in a Grid.
class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited = vector<vector<bool>>(m, vector<bool>(n, false));
        
        vector<vector<vector<int>>> dirs ={
            {{0,-1}, {0,1}},
            {{-1,0}, {1,0}},
            {{0,-1}, {1,0}},
            {{0,1}, {1,0}},
            {{0,-1}, {-1,0}},
            {{-1,0}, {0,1}}
        };
        
        queue<vector<int>> q;
        
        q.push({0,0});
        
        while(!q.empty()){
            vector<int> cur = q.front(); q.pop();
            int i = cur[0], j = cur[1];
            int type = grid[i][j]-1;
            // cout << i << " " << j << endl;
            visited[i][j] = true;
            
            for(vector<int>& dir : dirs[type]){
                //next position
                int ni = i + dir[0], nj = j + dir[1];
                //not valid position or already visited
                if(ni < 0 || ni >= m || nj < 0 || nj >= n || visited[ni][nj]){
                    continue;
                }
                int ntype = grid[ni][nj]-1;
                for(vector<int>& backdir : dirs[ntype]){
                    //the new position's street can connect to original position's street
                    if(ni + backdir[0] == i && nj + backdir[1] == j){
                        q.push({ni, nj});
                    }
                }
            }
        }
        
        return visited[m-1][n-1];
    }
};

//disjoint set unit DSU
//https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/discuss/547229/Python-Union-Find
//Runtime: 564 ms, faster than 25.21% of C++ online submissions for Check if There is a Valid Path in a Grid.
//Memory Usage: 41.9 MB, less than 100.00% of C++ online submissions for Check if There is a Valid Path in a Grid.
//time: O(m*n)*O(union find), space: O(m*n)
class DSU{
public:
    vector<int> parent;
    
    DSU(int size){
        parent = vector<int>(size);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };
    
    void unite(int x, int y){
        parent[find(x)] = find(y);
    }
};

class Solution {
public:
    int n;
    
    int getId(int i, int j){
        return 2*i*n + j;
    };
    
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        //used by getId
        this->n = n;
        
        //each grid has 4 points: its center, right, bottom, and bottom right
        //we only use center, right and bottom
        DSU dsu = DSU((2*m) * (2*n));
        
        //this type of street can connect to top
        set<int> top = {2,5,6};
        set<int> bottom = {2,3,4};
        set<int> left = {1,3,5};
        set<int> right = {1,4,6};
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                int cur = grid[i][j];
                //current grid's center
                int curId = getId(2*i, 2*j);
                int nextId;
                
                if(top.find(cur) != top.end()){
                    nextId = getId(2*i-1, 2*j);
                    if(nextId >= 0){
                        //connect this grid's center and its top
                        //current grid's top is just its top grid's bottom
                        dsu.unite(nextId, curId);
                    }
                }
                
                if(bottom.find(cur) != bottom.end()){
                    nextId = getId(2*i+1, 2*j);
                    if(nextId >= 0){
                        dsu.unite(nextId, curId);
                    }
                }
                
                if(left.find(cur) != left.end()){
                    nextId = getId(2*i, 2*j-1);
                    if(nextId >= 0){
                        dsu.unite(nextId, curId);
                    }
                }
                
                if(right.find(cur) != right.end()){
                    nextId = getId(2*i, 2*j+1);
                    if(nextId >= 0){
                        dsu.unite(nextId, curId);
                    }
                }
            }
        }
        
        /*
        if grid(0,0) and grid(m-1,n-1)'s center are 
        in the same disjoint set unit, 
        then they are connected
        */
        return dsu.find(0) == dsu.find(getId((m-1)*2, ((n-1)*2)));
    }
};
