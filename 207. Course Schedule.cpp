//https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
//Runtime: 32 ms, faster than 32.36% of C++ online submissions for Course Schedule.
//Memory Usage: 12.8 MB, less than 96.36% of C++ online submissions for Course Schedule.
class Solution {
public:
    bool isCyclicUtil(int cur, unordered_map<int, vector<int>>& edges, vector<bool>& visited, vector<bool>& recStack){
        visited[cur] = true;
        recStack[cur] = true;
        
        /*
        3
        [[0,1],[0,2],[1,2]]
        In the example: 
        */
        
        for(int nei : edges[cur]){
            // cout << cur << " -- " << nei << endl;
            if(!visited[nei]){
                if(isCyclicUtil(nei, edges, visited, recStack)){
                    return true;
                }
            }else if(recStack[nei]){
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
            edges[pre[0]].push_back(pre[1]);
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