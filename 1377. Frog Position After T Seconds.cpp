//Runtime: 44 ms, faster than 28.71% of C++ online submissions for Frog Position After T Seconds.
//Memory Usage: 10.8 MB, less than 100.00% of C++ online submissions for Frog Position After T Seconds.
class Solution {
public:
    // unordered_map<int, vector<int>> children;
    vector<vector<bool>> adj;
    vector<bool> visited;
    int target;
    vector<int> path;
    
    bool dfs(int node){
        if(node == target){
            path.insert(path.begin(), node);
            return true;
        }
        // for(int child : children[node]){
        for(int child = 1; child <= (int)adj.size()-1; child++){
            if(!adj[node][child] || visited[child]) continue;
            // cout << node << "----" << child << endl;
            visited[child] = true;
            //cut the reverse directed edge
            adj[child][node] = false;
            if(dfs(child)){
                path.insert(path.begin(), node);
                return true;
            }
        }
        return false;
    };
    
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        adj = vector(n+1, vector(n+1, false)); //0 is for padding
        visited = vector(n+1, false); //need to use this because the tree is undirected
        
        for(vector<int>& edge : edges){
            // children[edge[0]].push_back(edge[1]);
            adj[edge[0]][edge[1]] = adj[edge[1]][edge[0]] = true;
        }
        this->target = target;
        
        dfs(1);
        visited[1] = true;
        
        if(t < (int)path.size()-1){
            //not enough time
            return 0.0;
        }
        // else if(t > path.size()-1 && children[target].size() > 0){
        else if(t > path.size()-1 && accumulate(adj[target].begin()+1, adj[target].end(), 0) > 0){
            //too much time, and the target has children
            //so the frog won't stop at target
            return 0.0;
        }
        
        // cout << "path length: " << (int)path.size()-1 << endl;
        double ans = 1.0;
        for(int i = 0; i < (int)path.size()-1; i++){
            // ans *= 1.0/children[path[i]].size();
            int childCount = accumulate(adj[path[i]].begin()+1, adj[path[i]].end(), 0);
            // cout << "node: " << path[i] << ", children: " << childCount << endl;
            ans *= 1.0/childCount; 
            // cout << path[i] << " ";
        }
        // cout << endl;
        
        return ans;
    }
};

//BFS
//https://leetcode.com/problems/frog-position-after-t-seconds/discuss/532505/Java-Straightforward-BFS-Clean-code-O(N)
//Runtime: 24 ms, faster than 69.53% of C++ online submissions for Frog Position After T Seconds.
//Memory Usage: 11.3 MB, less than 100.00% of C++ online submissions for Frog Position After T Seconds.
class Solution {
public:
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        vector<vector<int>> children(n+1);
        vector<bool> visited(n+1, false);
        vector<double> prob(n+1, 0.0);
        queue<int> q;
        
        for(vector<int>& edge : edges){
            children[edge[0]].push_back(edge[1]);
            children[edge[1]].push_back(edge[0]);
        }
        
        q.push(1);
        visited[1] = true;
        prob[1] = 1.0;
        //we can only go to "t"th levels
        while(!q.empty() && t-- > 0){
            for(int levelCount = q.size(); levelCount > 0; levelCount--){
                int node = q.front(); q.pop();
                int nextLevelCount = 0;
                for(int child : children[node]){
                    if(!visited[child])nextLevelCount++;
                }
                for(int child : children[node]){
                    if(visited[child]) continue;
                    visited[child] = true;
                    prob[child] = prob[node] / nextLevelCount;
                    q.push(child);
                }
                if(nextLevelCount > 0){
                    //current node is not leaf
                    prob[node] = 0.0;
                }
            }
        }
        return prob[target];
    }
};
