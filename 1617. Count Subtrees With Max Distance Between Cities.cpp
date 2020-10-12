//enumerate all possible subtrees and calculate their maximum distances
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
