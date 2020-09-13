//priority_queue + dsu
//TLE
//71 / 72 test cases passed.
class DSU{
public:
    int n;
    vector<int> parent;
    
    DSU(int n){
        this->n = n;
        parent = vector<int>(n);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        
        return parent[x];
    }
    
    void unite(int x, int y){
        int px = find(x);
        int py = find(y);
        
        parent[py] = px;
    }
    
    bool isConnected(int x, int y){
        return (find(x) == find(y));
    }
};

class Solution {
public:
    int getDist(vector<int>& pi, vector<int>& pj){
        return abs(pi[0]-pj[0]) + abs(pi[1]-pj[1]);
    }
    
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        
        if(n == 1) return 0;
        
        
        // vector<vector<int>> graph(n, vector<int>(n, INT_MAX));
        
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        
        for(int i = 0; i < n; ++i){
            // graph[i][i] = 0;
            vector<int>& pi = points[i];
            for(int j = i+1; j < n; ++j){
                vector<int>& pj = points[j];
                int dist = getDist(pi, pj);
                // graph[i][j] = graph[j][i] = dist; 
                pq.push({dist, i, j});
            }
        }
        
        //edges needed
        int need = n-1;
        int ans = 0;
        DSU dsu(n);
        
        while(need > 0){
            vector<int> edge = pq.top(); pq.pop();
            int dist = edge[0], src = edge[1], dst = edge[2];
            
            if(dsu.isConnected(src, dst))
                continue;
            
            dsu.unite(src, dst);
            ans += dist;
            --need;
        }
        
        return ans;
    }
};
