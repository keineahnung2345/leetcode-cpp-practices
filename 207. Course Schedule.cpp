//https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
//Runtime: 24 ms, faster than 64.54% of C++ online submissions for Course Schedule.
//Memory Usage: 12.7 MB, less than 100.00% of C++ online submissions for Course Schedule.
class Solution {
public:
    bool isCyclicUtil(int cur, unordered_map<int, vector<int>>& edges, vector<bool>& visited, vector<bool>& recStack){
        visited[cur] = true;
        recStack[cur] = true;
        
        /*
        3
        [[0,1],[0,2],[1,2]]
        (according to the problem description, the edge is represented as [dst, src])
        In the example: 
        there are two paths :
        2->0
        2->1->0
        If we go through the first path first, 0 will be marked as visited,
        later when we go through the second path, we will see 0 as visited,
        if we only use "visited" to detect cycle, it will fail in this case,
        so we need "recStack" to check if 0 is on our path
        */
        
        for(int nei : edges[cur]){
            // cout << cur << " -- " << nei << endl;
            /*
            the first part can be written as:
            if(!visited[nei] && isCyclicUtil(nei, edges, visited, recStack))
            because in the second part, if recStack[nei] is true, 
            then visited[nei] must be true, so it will skip first part anyway
            */
            if(!visited[nei]){
                //find whether its neighbor is cyclic
                if(isCyclicUtil(nei, edges, visited, recStack)){
                    return true;
                }
            }else if(recStack[nei]){
                //that means nei is both cur's ancestor and its descendent
                // cout << cur << " -- " << nei << ", nei in recStack" << endl;
                return true;
            }
        }
        
        //recStack is restored(because we finish this layer of recursion)
        recStack[cur] = false;
        
        //Note that visited[cur] is not restored
        
        return false;
    };
    
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<bool> visited(numCourses, false);
        vector<bool> recStack(numCourses, false);
        
        bool hasCycle = false;
        
        unordered_map<int, vector<int>> edges;
        for(vector<int>& pre : prerequisites){
            /*
            this is correct according to the problem definition
            pre[1] should be taken before pre[0],
            so the edge is from pre[1] to pre[0]
            */
            edges[pre[1]].push_back(pre[0]);
            //however this also gives correct answer
            // edges[pre[0]].push_back(pre[1]);
        }
        
        for(int i = 0; i < numCourses; i++){
            if(!visited[i]){
                if(isCyclicUtil(i, edges, visited, recStack)){
                    //we have cycle
                    hasCycle = true;
                    break;
                }
            }
        }
        
        return !hasCycle;
    }
};

//topological sort, bfs
//https://leetcode.com/problems/course-schedule/discuss/58516/Easy-BFS-Topological-sort-Java
//Runtime: 24 ms, faster than 64.54% of C++ online submissions for Course Schedule.
//Memory Usage: 10.8 MB, less than 100.00% of C++ online submissions for Course Schedule.
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> incomingEdgeCount(numCourses, 0);
        vector<vector<int>> edges(numCourses);
        
        for(vector<int>& pre : prerequisites){
            //pre[1] points to pre[0](pre[1] should be taken before pre[0])
            incomingEdgeCount[pre[0]]++;
            edges[pre[1]].push_back(pre[0]);
        }
        
        queue<int> noIncomingEdges;
        for(int i = 0; i < numCourses; i++){
            if(incomingEdgeCount[i] == 0){
                noIncomingEdges.push(i);
            }
        }
        
        int remainingEdgeCount = prerequisites.size();
        while(!noIncomingEdges.empty()){
            int cur = noIncomingEdges.front(); noIncomingEdges.pop();
            for(int nei : edges[cur]){
                remainingEdgeCount--;
                if(--incomingEdgeCount[nei] == 0){
                    noIncomingEdges.push(nei);
                }
            }
        }
        //if there are redundant edges, there is a cycle
        return remainingEdgeCount == 0;
    }
};
