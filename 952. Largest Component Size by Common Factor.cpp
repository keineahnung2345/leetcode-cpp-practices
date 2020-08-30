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
