//Union find
//originally thought as a graph problem
//hint: Always use Type 3 edges first, and connect the still isolated ones using other edges.
//Runtime: 1236 ms, faster than 75.00% of C++ online submissions for Remove Max Number of Edges to Keep Graph Fully Traversable.
//Memory Usage: 139 MB, less than 50.00% of C++ online submissions for Remove Max Number of Edges to Keep Graph Fully Traversable.
class DSU{
public:
    int n;
    vector<int> parent;
    vector<int> sz;
    int max_sz;
    
    DSU(int n){
        this->n = n;
        parent = vector<int>(n);
        iota(parent.begin(), parent.end(), 0);
        sz = vector<int>(n, 1);
        max_sz = 1;
    }
    
    int find(int x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    int unite(int x, int y){
        if(x > y) swap(x, y);
        //merge the later to the earlier
        
        int py = find(y);
        int px = find(x);
        
        if(px == py)
            return -1;
        
        parent[py] = px;
        sz[px] += sz[py];
        max_sz = max(max_sz, sz[px]);
        
        return 0;
    }
};

class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        sort(edges.begin(), edges.end(), 
            [](vector<int>& e1, vector<int>& e2){return e1[0] > e2[0];});
        
        DSU dsu1(n), dsu2(n);
        int discarded = 0;
        
        for(vector<int>& edge : edges){
            // cout << edge[0] << ", " << edge[1] << ", " << edge[2] << endl;
            switch(edge[0]){
                case 1:
                    if(dsu1.unite(edge[1]-1, edge[2]-1)){
                        ++discarded;
                        // cout << "discard" << endl;
                    }
                    // cout << "dsu1 max size: " << dsu1.max_sz << endl;
                    break;
                case 2:
                    if(dsu2.unite(edge[1]-1, edge[2]-1)){
                        ++discarded;
                        // cout << "discard" << endl;
                    }
                    // cout << "dsu2 max size: " << dsu2.max_sz << endl;
                    break;
                case 3:
                    int ret = dsu1.unite(edge[1]-1, edge[2]-1);
                    dsu2.unite(edge[1]-1, edge[2]-1);
                    
                    if(ret){
                        //they are originally in the same union
                        //since dsu1 is the same as dsu2 when processing type 3,
                        //so only need to check dsu1
                        ++discarded;
                        // cout << "discard" << endl;
                    }
                    // cout << "max size: " << dsu1.max_sz << endl;
            }
        }
        
        if(dsu1.max_sz != n || dsu2.max_sz != n){
            //the graph is not fully connected
            return -1;
        }
        
        return discarded;
    }
};
