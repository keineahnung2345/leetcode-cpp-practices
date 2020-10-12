//Runtime: 240 ms, faster than 50.00% of C++ online submissions for Maximal Network Rank.
//Memory Usage: 45.6 MB, less than 50.00% of C++ online submissions for Maximal Network Rank.
struct vec_hash_int {
    inline std::size_t operator()(const std::vector<int> & v) const {
        return v[0]*31+v[1];
    }
};

class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        int ans = 0;
        
        vector<int> degrees(n, 0);
        unordered_set<vector<int>, vec_hash_int> edges;
        
        for(vector<int>& road : roads){
            if(road[0] > road[1]) swap(road[0], road[1]);
            edges.insert(road);
            ++degrees[road[0]];
            ++degrees[road[1]];
        }
        
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                int connected = (edges.find({i,j}) != edges.end());
                ans = max(ans, degrees[i] + degrees[j] - connected);
            }
        }
        
        return ans;
    }
};
