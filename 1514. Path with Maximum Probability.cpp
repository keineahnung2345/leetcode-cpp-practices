//DFS
//TLE
//10 / 16 test cases passed.
class Solution {
public:
    vector<vector<pair<int, double>>> adj;
    
    void dfs(int cur, int end, double prob, double& ans, vector<bool>& visited){
        if(cur == end){
            ans = max(ans, prob);
        }else{
            for(pair<int, double>& neiEdge : adj[cur]){
                if(!visited[neiEdge.first] && prob * neiEdge.second > ans){
                    visited[neiEdge.first] = true;
                    dfs(neiEdge.first, end, prob * neiEdge.second, ans, visited);
                    visited[neiEdge.first] = false;
                }
            }
        }
    };
    
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        adj = vector<vector<pair<int, double>>>(n);
        
        for(int i = 0; i < edges.size(); ++i){
            adj[edges[i][0]].push_back({edges[i][1], succProb[i]});
            adj[edges[i][1]].push_back({edges[i][0], succProb[i]});
        }
        
        // cout << "adj done" << endl;
        
        double ans = 0.0;
        vector<bool> visited(n, false);
        visited[start] = true;
        
        dfs(start, end, 1.0, ans, visited);
        
        return ans;
    }
};

//Bellman Ford
//https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
//http://courses.csail.mit.edu/6.006/spring11/lectures/lec15.pdf
//TLE
//10 / 16 test cases passed.
//time: O(VE)
class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        //max probability from start node
        vector<double> maxProb(n, 0.0);
        maxProb[start] = 1.0;
        
        //relax for |V|-1 times, because a simple path can have at most |V|-1 edges
        for(int i = 1; i <= n-1; ++i){
            //try to add one edge to paths
            for(int j = 0; j < edges.size(); ++j){
                //the graph is undirected!
                maxProb[edges[j][1]] = max(maxProb[edges[j][1]], maxProb[edges[j][0]] * succProb[j]);
                maxProb[edges[j][0]] = max(maxProb[edges[j][0]], maxProb[edges[j][1]] * succProb[j]);
            }
        }
        
        return maxProb[end];
    }
};

//Bellman Ford, BFS, SPFA(shortest path faster algorithm), not understand(does it repeat for |V|-1 times?) 
//https://leetcode.com/problems/path-with-maximum-probability/discuss/731626/Java-Detailed-Explanation-BFS
//https://www.geeksforgeeks.org/shortest-path-faster-algorithm/
//Runtime: 576 ms, faster than 12.50% of C++ online submissions for Path with Maximum Probability.
//Memory Usage: 68.9 MB, less than 100.00% of C++ online submissions for Path with Maximum Probability.
class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        vector<vector<pair<int, double>>> adjList(n);
        
        for(int i = 0; i < edges.size(); ++i){
            adjList[edges[i][0]].push_back({edges[i][1], succProb[i]});
            adjList[edges[i][1]].push_back({edges[i][0], succProb[i]});
        }
        
        //max probability from start node
        vector<double> maxProb(n, 0.0);
        maxProb[start] = 1.0;
        
        queue<pair<int, double>> q;
        q.push({start, 1.0});
        
        while(!q.empty()){
            pair<int, double> cur = q.front(); q.pop();
            int curNode = cur.first;
            double curProb = cur.second;
            
            for(pair<int, double>& nei : adjList[curNode]){
                int neiNode = nei.first;
                double neiProb = nei.second;
                
                if(curProb * neiProb > maxProb[neiNode]){
                    maxProb[neiNode] = max(maxProb[neiNode], curProb * neiProb);
                    q.push({neiNode, maxProb[neiNode]});
                }
            }
        }
        
        return maxProb[end];
    }
};

//Dijkstra's algorithm
//https://www.geeksforgeeks.org/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/
//https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
//https://leetcode.com/problems/path-with-maximum-probability/discuss/731626/Java-Detailed-Explanation-BFS
//Runtime: 460 ms, faster than 12.50% of C++ online submissions for Path with Maximum Probability.
//Memory Usage: 66.2 MB, less than 100.00% of C++ online submissions for Path with Maximum Probability.
//time: O((V+E)logV), we may push E elements into heap, and it takes O(logV) to pop, space: O(V+E)
class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        vector<vector<pair<int, double>>> adjList(n);
        
        for(int i = 0; i < edges.size(); ++i){
            adjList[edges[i][0]].push_back({edges[i][1], succProb[i]});
            adjList[edges[i][1]].push_back({edges[i][0], succProb[i]});
        }
        
        //max probability from start node
        vector<double> maxProb(n, 0.0);
        maxProb[start] = 1.0;
        
        auto comp = [](pair<int, double>& a, pair<int, double>& b){return a.second < b.second;};
        priority_queue<pair<int, double>, vector<pair<int, double>>, decltype(comp)> pq(comp);
        
        pq.push({start, maxProb[start]});
        
        //while there are nodes that are not in SPT set
        while(!pq.empty()){
            /*
            dijkstra's algorithm: greedy
            it find the node with highest probability and 
            add it to the set containing all nodes already 
            included in SPT(shortest path tree)
            */
            pair<int, double> cur = pq.top(); pq.pop();
            int curNode = cur.first;
            double curProb = cur.second;
            
            if(curNode == end){
                /*
                the node "end" has been added to SPT set,
                that means we have found shortest path
                from start to end
                */
                //early stopping?
                //cannot do early stopping in bellman ford?
                break;
            }
            
            //we still need to visit all neighbors of curNode, what's the meaning of using priority_queue?
            for(pair<int, double>& nei : adjList[curNode]){
                int neiNode = nei.first;
                double neiProb = nei.second;
                
                if(curProb * neiProb > maxProb[neiNode]){
                    maxProb[neiNode] = max(maxProb[neiNode], curProb * neiProb);
                    pq.push({neiNode, maxProb[neiNode]});
                }
            }
        }
        
        return maxProb[end];
    }
};

//Floyd–Warshall
//https://leetcode.com/problems/path-with-maximum-probability/discuss/731626/Java-Detailed-Explanation-BFS
//https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/
//TLE
//9 / 16 test cases passed.
//time: O(V^3)
class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        vector<vector<double>> maxProbs(n, vector<double>(n, 0.0));
        
        for(int i = 0; i < edges.size(); ++i){
            maxProbs[edges[i][0]][edges[i][1]] = succProb[i];
            maxProbs[edges[i][1]][edges[i][0]] = succProb[i];
        }
        
        for(int k = 0; k < n; ++k){
            for(int i = 0; i < n; ++i){
                for(int j = 0; j < n; ++j){
                    //relax edge (i, j) with node k
                    maxProbs[i][j] = max(maxProbs[i][j], maxProbs[i][k] * maxProbs[k][j]);
                }
            }
        }
        
        return maxProbs[start][end];
    }
};
