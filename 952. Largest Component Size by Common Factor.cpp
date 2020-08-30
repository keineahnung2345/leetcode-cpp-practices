//Graph, BFS
//TLE
//71 / 100 test cases passed.
class Solution {
public:
    int gcd(int x, int y){
        if(x < y){
            swap(x, y);
        }
        
        if(y == 0){
            return x;
        }
        
        return gcd(y, x%y);
    };
    
    int largestComponentSize(vector<int>& A) {
        int ans = 0;
        
        int n = A.size();
        
        unordered_map<int, unordered_set<int>> graph;
        
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                if(gcd(A[i], A[j]) > 1){
                    graph[i].insert(j);
                    graph[j].insert(i);
                }
            }
        }
        
        vector<bool> visited(n, false);
        
        for(int i = 0; i < n; ++i){
            if(visited[i]) continue;
            
            int comp_size = 0;
            
            queue<int> q;
            q.push(i);
            visited[i] = true;
            
            while(!q.empty()){
                int cur = q.front(); q.pop();
                ++comp_size;
                
                for(int nei : graph[cur]){
                    if(!visited[nei]){
                        visited[nei] = true;
                        q.push(nei);
                    }
                }
            }
            
            ans = max(ans, comp_size);
        }
        
        return ans;
    }
};

//Union find
//TLE
//74 / 100 test cases passed.
class DSU{
public:
    vector<int> parent;
    
    DSU(int n){
        parent = vector<int>(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        
        return parent[x];
    }
    
    void unite(int x, int y){
        //merge the larger to the smaller
        parent[find(y)] = find(x);
    }
};

class Solution {
public:
    int gcd(int x, int y){
        if(x < y) swap(x, y);
        if(y == 0) return x;
        return gcd(y, x%y);
    };
    
    int largestComponentSize(vector<int>& A) {
        int n = A.size();
        
        DSU dsu(n);
        
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                if(gcd(A[i], A[j]) > 1){
                    dsu.unite(i, j);
                }
            }
        }
        
        unordered_map<int, int> group2count;
        int ans = 0;
        
        for(int i = 0; i < n; ++i){
            ++group2count[dsu.find(i)];
            ans = max(ans, group2count[dsu.find(i)]);
        }
        
        return ans;
    }
};

//Union find + precompute prime numbers
//TLE
//78 / 100 test cases passed.
class DSU{
public:
    vector<int> parent;
    
    DSU(int n){
        parent = vector<int>(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        
        return parent[x];
    }
    
    void unite(int x, int y){
        //merge the larger to the smaller
        parent[find(y)] = find(x);
    }
};

class Solution {
public:
    vector<bool> isprime;
    
    void SieveOfEratosthenes(int n){
        for(int p=2; p*p<=n; p++){ 
            if(isprime[p]){
                for(int i=p*p; i<=n; i += p)
                    isprime[i] = false;
            }
        }
    };
    
    int largestComponentSize(vector<int>& A) {
        int n = A.size();
        
        int max_ele = *max_element(A.begin(), A.end());
        isprime = vector<bool>(max_ele+1, true);
        SieveOfEratosthenes(max_ele);
        
        // cout << "max: " << max_ele << endl;
        
        unordered_set<int> primes;
        for(int p = 2; p <= max_ele; ++p){
            if(isprime[p]){
                primes.insert(p);
            }
        }
        
        DSU dsu(max_ele+1);
        
        for(int p : primes){
            for(int i = 0; i < n; ++i){
                if(A[i]%p == 0){
                    dsu.unite(p, A[i]);
                }
            }
        }
        
        unordered_map<int, int> group2count;
        int ans = 0;
        
        for(int i = 0; i < n; ++i){
            ++group2count[dsu.find(A[i])];
            ans = max(ans, group2count[dsu.find(A[i])]);
        }
        
        return ans;
    }
};
