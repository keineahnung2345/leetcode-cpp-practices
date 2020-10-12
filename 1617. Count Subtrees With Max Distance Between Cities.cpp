//enumerate all possible subtrees, check if they are valid, and calculate their maximum distances
//not sure if the "checking is a tree" part is correct or not
//Runtime: 1572 ms, faster than 8.33% of C++ online submissions for Count Subtrees With Max Distance Between Cities.
//Memory Usage: 132 MB, less than 8.33% of C++ online submissions for Count Subtrees With Max Distance Between Cities.
class Solution {
public:
    int sizeOfTree(int subtree){
        int size = 0;
        
        while(subtree){
            if(subtree & 1){
                ++size;
            }
            subtree >>= 1;
        }
        
        return size;
    }

    bool isTree(int subtree, int& size, vector<vector<int>>& adjList, vector<int>& nodes){
        int node = 1;
        
        // cout << "tree: ";
        
        while(subtree){
            if(subtree & 1){
                // cout << node << " ";
                nodes.push_back(node);
            }
            ++node;
            subtree >>= 1;
        }
        // cout << endl;
        
        size = nodes.size();
        
        //extra condition
        if(size <= 1) return false;
        
        int edgeCount = 0;
        
        for(int i = 0; i < size; ++i){
            for(int j = i+1; j < size; ++j){
                auto it = find(adjList[nodes[i]].begin(), adjList[nodes[i]].end(), nodes[j]);
                if(it == adjList[nodes[i]].end()) continue;
                ++edgeCount;
            }
        }
        
        // cout << "edgeCount: " << edgeCount << endl;
        
        return (edgeCount == size-1);
    }
    
    pair<int, int> bfs(int start, vector<int>& nodes, vector<vector<int>>& adjList){
        queue<int> q;
        unordered_set<int> visited;
        
        q.push(start);
        visited.insert(start);
        
        int dist = 0;
        int farthestNode = -1;
        
        while(!q.empty()){
            int level_size = q.size();
            
            while(level_size--){
                int cur = q.front(); q.pop();
                farthestNode = cur;
            
                for(int& nei : adjList[cur]){
                    if(find(nodes.begin(), nodes.end(), nei) == nodes.end()) continue;
                    if(visited.find(nei) != visited.end()) continue;
                    visited.insert(nei);
                    q.push(nei);
                }
            }
            
            ++dist;
        }
        
        return {dist-1, farthestNode};
    }
    
    int maxDist(vector<int>& nodes, vector<vector<int>>& adjList){
        // cout << "tree: " << endl;
        // for(int& node : nodes) cout << node << " ";
        // cout << endl;
        
        pair<int, int> p1 = bfs(nodes[0], nodes, adjList);
        // cout << nodes[0] << " -> " << p1.second << " : " << p1.first << endl;
        pair<int, int> p2 = bfs(p1.second, nodes, adjList);
        // cout << p1.second << " -> " << p2.second << " : " << p2.first << endl;
        
        // cout << "maxDist: " << p2.first << endl;
        return p2.first;
    }
    
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        //distance from 1 to n-1
        vector<int> ans(n-1, 0);
        
        vector<vector<int>> adjList(n+1);
        
        for(vector<int>& edge : edges){
            if(edge[0] > edge[1]) swap(edge[0], edge[1]);
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }
        
        for(int subtree = 0; subtree < (1<<n); ++subtree){
            // if(sizeOfTree(subtree) <= 1) continue;
            // vector<int> usable;
            int size;
            vector<int> nodes;
            if(!isTree(subtree, size, adjList, nodes)) continue;
            ++ans[maxDist(nodes, adjList)-1];
        }
        
        return ans;
    }
};

//enumerate all possible subtrees, check if they are valid, and calculate their maximum distances by tree diameter
//https://leetcode.com/problems/count-subtrees-with-max-distance-between-cities/discuss/889070/Python-Bitmask-try-all-subset-of-cities-Clean-and-Concise-O(2n-*-n)
//Runtime: 1532 ms, faster than 8.33% of C++ online submissions for Count Subtrees With Max Distance Between Cities.
//Memory Usage: 370.5 MB, less than 8.33% of C++ online submissions for Count Subtrees With Max Distance Between Cities.
class Solution {
public:
    vector<int> bfs(int src, vector<int>& nodes, vector<vector<int>>& adjList){
        queue<int> q;
        //index 0: dummy
        vector<bool> visited(adjList.size(), false);
        
        //will be the farthest point from src
        int last = src;
        //the distance between src and farthest point
        int dist = 0;
        
        q.push(src);
        visited[src] = true;
        
        while(!q.empty()){
            int level_size = q.size();
            
            while(level_size-- > 0){
                int cur = q.front(); q.pop();
                last = cur;
                
                for(const int& nei : adjList[cur]){
                    //can only use edges in this subtree!!
                    if(find(nodes.begin(), nodes.end(), nei) == nodes.end()) continue;
                    if(visited[nei]) continue;
                    visited[nei] = true;
                    q.push(nei);
                }
            }
            
            ++dist;
        }
        
        //dist is unnecessarily increased one time before exit
        --dist;
        
        return {static_cast<int>(count_if(visited.begin(), visited.end(), 
                         [](const bool& b){return b;})), 
                last,
                dist};
    }
    
    int diameterOfTree(vector<int>& nodes, vector<vector<int>>& adjList){
        if(nodes.size() <= 1)
            return 0;
        
        // cout << "nodes: ";
        // for(const int& node : nodes){
        //     cout << node << " ";
        // }
        // cout << endl;
        
        vector<int> v = bfs(nodes[0], nodes, adjList);
        
        //cannot visit all nodes, that means the tree is not connected
        if(v[0] < nodes.size())
            return 0;
        
        v = bfs(v[1], nodes, adjList);
        
        // cout << v[2] << endl;
        
        return v[2];
    }
    
    int maxDistance(int state, vector<vector<int>>& adjList){
        vector<int> nodes;
        
        int i = 1;
        while(state){
            if(state & 1) 
                nodes.push_back(i);
            state >>= 1;
            ++i;
        }
        
        return diameterOfTree(nodes, adjList);
    }
    
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        //index 0: dummy
        vector<vector<int>> adjList(n+1);
        
        for(const vector<int>& edge : edges){
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }
        
        vector<int> ans(n-1, 0);
        
        for(int state = 1; state < (1<<n); ++state){
            int md = maxDistance(state, adjList);
            //md == 0 means cities is not a valid tree
            if(md > 0) ++ans[md-1];
        }
        
        return ans;
    }
};
