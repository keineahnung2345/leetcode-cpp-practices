/**
Given a directed, acyclic graph of N nodes.  Find all possible paths from node 0 to node N-1, and return them in any order.

The graph is given as follows:  the nodes are 0, 1, ..., graph.length - 1.  graph[i] is a list of all nodes j for which the edge (i, j) exists.

Example:
Input: [[1,2], [3], [3], []] 
Output: [[0,1,3],[0,2,3]] 
Explanation: The graph looks like this:
0--->1
|    |
v    v
2--->3
There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
Note:

The number of nodes in the graph will be in the range [2, 15].
You can print different paths in any order, but you should keep the order of nodes inside one path.
**/

//Your runtime beats 53.33 % of cpp submissions.
class Solution {
public:
    vector<vector<int>> oneSourceTarget(vector<vector<int>>& graph, int src, vector<int>& fromPath){
        vector<vector<int>> toPaths;
        vector<int> fromPath2 = vector<int>(fromPath);
        fromPath2.push_back(src);
        
        for(int i = 0; i < graph[src].size(); i++){
            if(graph[src][i]!=graph.size()-1){ 
                //not goal, then keep going
                vector<vector<int>> results = oneSourceTarget(graph, graph[src][i], fromPath2);
                //similar to python's toPaths.extend(results)
                if(!results.empty()){
                    //https://stackoverflow.com/questions/313432/c-extend-a-vector-with-another-vector
                    toPaths.reserve(toPaths.size() + distance(results.begin(),results.end()));
                    toPaths.insert(toPaths.end(),results.begin(),results.end());
                }
            }else{ 
                //achieve goal, then prepare the result and then return
                vector<int> toPath(fromPath2);
                toPath.push_back(graph[src][i]);
                toPaths.push_back(toPath);
            }
        }
        //toPaths.empty() will be true if no paths to target
        return toPaths; 
    }
    
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<int> fromPath;
        vector<vector<int>> toPaths;
        
        vector<vector<int>> curToPaths = oneSourceTarget(graph, 0, fromPath);
            
        // reserve() is optional - just to improve performance
        toPaths.reserve(toPaths.size() + distance(curToPaths.begin(),curToPaths.end()));
        toPaths.insert(toPaths.end(),curToPaths.begin(),curToPaths.end());
        
        return toPaths;
    }
};

/**
Approach #1: Recursion [Accepted]
Intuition

Since the graph is a directed, acyclic graph, any path from A to B is going to be composed of A plus a path from any neighbor of A to B. We can use a recursion to return the answer.

Algorithm

Let N be the number of nodes in the graph. If we are at node N-1, the answer is just the path {N-1}. Otherwise, if we are at node node, the answer is {node} + {path from nei to N-1} for each neighbor nei of node. This is a natural setting to use a recursion to form the answer.

//This is the answer adpated from the solution which is originally Java version
//Your runtime beats 48.17 % of cpp submissions.
class Solution {
public:
    vector<vector<int>> solve(vector<vector<int>>& graph, int node){
        int N = graph.size();
        vector<vector<int>> ans;
        if(node==N-1){
            vector<int> path;
            //construct the path from the end
            path.push_back(node);
            ans.push_back(path);
            return ans;
        }
        
        for(int i = 0; i < graph[node].size(); i++){
            int nei = graph[node][i];
            for(vector<int> path : solve(graph, nei)){
                //prefix the returned path with current node
                //the returned path includes "nei"
                path.insert(path.begin(), node); //vector.insert() is in-place
                ans.push_back(path);
            }
        }
        
        return ans;
    }
    
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        return solve(graph, 0);  
    }
};

Complexity Analysis

Time Complexity: O(2^N*N^2). We can have exponentially many paths, and for each such path, 
our prepending operation path.add(0, node) will be O(N^2).

Space Complexity: O(2^N*N), the size of the output dominating the final space complexity.
**/
