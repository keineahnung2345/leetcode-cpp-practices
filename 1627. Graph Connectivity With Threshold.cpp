//graph
//WA
//57 / 66 test cases passed.
//indirectly connection also considered true?
class Solution {
public:
    int gcd(int x, int y){
        if(y == 0) return x;
        return gcd(y, x%y);
    }
    
    int encode(int& i, int& j, int& n){
        return i*(n+1)+j;
    }
    
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
        int m = queries.size();
        vector<bool> ans(m, true);
        
        if(threshold == 0){
            return ans;
        }
        
        unordered_set<int> edges;
        
        for(int i = 1; i <= n; ++i){
            for(int j = i+1; j <= n; ++j){
                if(gcd(i, j) > threshold){
                    edges.insert(encode(i, j, n));
                }
            }
        }
        
        for(int i = 0; i < m; ++i){
            vector<int>& q = queries[i];
            if(q[0] > q[1]) swap(q[0], q[1]);
            
            ans[i] = (edges.find(encode(q[0], q[1], n)) != edges.end());
        }
        
        return ans;
    }
};

//graph
//fix above: indirectly connected cities should also be seen as connected
//TLE
//64 / 66 test cases passed.
class Solution {
public:
    int gcd(int x, int y){
        if(y == 0) return x;
        return gcd(y, x%y);
    }
    
    int encode(int& i, int& j, int& n){
        return i*(n+1)+j;
    }
    
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
        int m = queries.size();
        vector<bool> ans(m, true);
        
        if(threshold == 0){
            return ans;
        }
        
        vector<unordered_set<int>> adjList(n+1);
        
        for(int i = 1; i <= n; ++i){
            for(int j = i+1; j <= n; ++j){
                if(gcd(i, j) > threshold){
                    adjList[i].insert(j);
                    adjList[j].insert(i);
                }
            }
        }
        
        for(int i = 0; i < m; ++i){
            vector<int>& query = queries[i];
            if(query[0] > query[1]) swap(query[0], query[1]);
            
            bool connected = false;
            
            queue<int> q;
            vector<bool> visited(n+1, false);
            int cur;
            
            q.push(query[0]);
            visited[query[0]] = true;
            
            while(!q.empty()){
                cur = q.front(); q.pop();
                
                if(cur == query[1]){
                    connected = true;
                    break;
                }
                
                for(const int& nei : adjList[cur]){
                    if(visited[nei]) continue;
                    visited[nei] = true;
                    q.push(nei);
                }
            }
            
            ans[i] = connected;
        }
        
        return ans;
    }
};

//DSU
//from hint
//Runtime: 360 ms, faster than 57.32% of C++ online submissions for Graph Connectivity With Threshold.
//Memory Usage: 65.4 MB, less than 6.13% of C++ online submissions for Graph Connectivity With Threshold.
class DSU{
public:
    vector<int> parent;
    
    DSU(int n){
        parent = vector<int>(n);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x){
        if(parent[x] == x) return x;
        return find(parent[x]);
    }
    
    void unite(int x, int y){
        int px = find(x);
        int py = find(y);
        
        parent[py] = px;
    }
};

class Solution {
public:
    int gcd(int x, int y){
        if(y == 0) return x;
        return gcd(y, x%y);
    }
    
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
        int m = queries.size();
        vector<bool> ans(m, true);
        
        if(threshold == 0){
            return ans;
        }
        
        DSU dsu(n+1);
        
        for(int i = threshold+1; i <= n; ++i){
            for(int j = i*2; j <= n; j += i){
                //gcd(i, j) > threshold must hold!
                //if(gcd(i, j) > threshold){
                    dsu.unite(i, j);
                //}
            }
        }
        
        for(int i = 0; i < m; ++i){
            vector<int>& q = queries[i];
            
            ans[i] = dsu.find(q[0]) == dsu.find(q[1]);
        }
        
        return ans;
    }
};
