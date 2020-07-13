//Bellman Ford
//https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
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

//Bellman Ford, BFS, not understand(does it repeat for |V|-1 times?) 
//https://leetcode.com/problems/path-with-maximum-probability/discuss/731626/Java-Detailed-Explanation-BFS
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
