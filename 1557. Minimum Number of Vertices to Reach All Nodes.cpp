//Runtime: 716 ms, faster than 83.33% of C++ online submissions for Minimum Number of Vertices to Reach All Nodes.
//Memory Usage: 94.6 MB, less than 83.33% of C++ online submissions for Minimum Number of Vertices to Reach All Nodes.
class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        vector<int> indegree(n, 0);
        
        for(vector<int>& edge : edges){
            ++indegree[edge[1]];
        }
        
        vector<int> ans;
        
        for(int i = 0; i < n; ++i){
            if(indegree[i]== 0){
                ans.push_back(i);
            }
        }
        
        return ans;
    }
};
