//Runtime: 12 ms, faster than 71.71% of C++ online submissions for Regions Cut By Slashes.
//Memory Usage: 9.9 MB, less than 50.00% of C++ online submissions for Regions Cut By Slashes.
//Approach 1: Union-Find
class DSU{
public:
    vector<int> parent;
    
    DSU(int N){
        parent = vector<int>(N);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y){
        parent[find(x)] = find(y);
    }
};

class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        int N = grid.size();
        //0,1,2,3 for north, west, east, south
        DSU dsu = DSU(4*N*N);
        for(int r = 0; r < N; r++){
            for(int c = 0; c < N; c++){
                //one grid has max of 4 regions
                int root = 4 * (r*N+c);
                char val = grid[r][c];
                //Note here it is "!="
                if(val != '\\'){
                    //north and west are connected
                    dsu.unite(root + 0, root + 1);
                    //east and south are connected
                    dsu.unite(root + 2, root + 3);
                }
                if(val != '/'){
                    //north and east are connected
                    dsu.unite(root + 0, root + 2);
                    //west and south are connected
                    dsu.unite(root + 1, root + 3);
                }
                
                //connecting with other grids
                //connect south of current grid and north of the grid below
                if(r + 1 < N)
                    dsu.unite(root + 3, (root + 4*N) + 0);
                //north and upper's south
                if(r - 1 >= 0)
                    dsu.unite(root + 0, (root - 4*N) + 3);
                //east and rhs's west
                if(c + 1 < N)
                    dsu.unite(root + 2, (root + 4) + 1);
                //west and lhs's east
                if(c - 1 >= 0)
                    dsu.unite(root + 1, (root - 4) + 2);
            }
        }
        
        int ans = 0;
        for(int x = 0; x < 4*N*N; x++){
            if(dsu.find(x) == x)
                ans++;
        }
        
        return ans;
    }
};
