//Tarjan's algorithm, find bridge
//https://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/
//https://www.geeksforgeeks.org/bridge-in-a-graph/
//https://www.quora.com/q/competitiveprogramming2/Cut-Vertex-Articulation-point
//Runtime: 1356 ms, faster than 35.79% of C++ online submissions for Critical Connections in a Network.
//Memory Usage: 167.3 MB, less than 79.16% of C++ online submissions for Critical Connections in a Network.
class Solution {
public:
    void bridgeUtil(int cur, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& disc, vector<int>& low, vector<int>& parent, int& time, vector<vector<int>>& edges){
        visited[cur] = true;
        disc[cur] = low[cur] = time++;
        
        // cout << "discover " << cur << " at " << disc[cur] << endl;
        // cout << cur << " has " << adj[cur].size() << " neighbors." << endl;
        
        for(int nei : adj[cur]){
            if(!visited[nei]){
                parent[nei] = cur;
                bridgeUtil(nei, adj, visited, disc, low, parent, time, edges);
                /*
                low[cur]: earliest visited vertex reachable 
                from subtree rooted with cur
                
                because nei is a subtree of cur,
                so we can update low[cur] with low[nei]
                if low[nei] is smaller
                */
                low[cur] = min(low[cur], low[nei]);
                // if(low[cur] == low[nei]) cout << "through low[" << nei << "], low[" << cur << "]: " << low[cur] << endl;
                
                /*
                cur has a subtree rooted at nei,
                and nei cannot go to cur or 
                its ancestor through back edge
                */
                if(low[nei] > disc[cur]){
                    edges.push_back({cur, nei});
                }
            }else if(nei != parent[cur]){
                //not understand?
                low[cur] = min(low[cur], disc[nei]);
                // if(low[cur] == disc[nei]) cout << "through disc[" << nei << "], low[" << cur << "]: " << low[cur] << endl;
            }
        }
    };
    
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        //adjacency list
        vector<vector<int>> adj(n);
        
        for(vector<int>& conn : connections){
            //undirected graph
            adj[conn[0]].push_back(conn[1]);
            adj[conn[1]].push_back(conn[0]);
        }
        
        vector<bool> visited(n, false);
        vector<int> disc(n);
        //earliest visited vertex reachable from subtree rooted with v
        vector<int> low(n);
        vector<int> parent(n, -1);
        
        vector<vector<int>> edges;
        
        for(int i = 0; i < n; ++i){
            if(!visited[i]){
                // cout << "visit " << i << endl;
                int time = 0;
                bridgeUtil(i, adj, visited, disc, low, parent, time, edges);
            }
        }
        
        return edges;
    }
};
