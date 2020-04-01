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
