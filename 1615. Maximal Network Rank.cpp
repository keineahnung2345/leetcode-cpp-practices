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

//average O(NlogN), worst O(N^2)
//https://leetcode.com/problems/maximal-network-rank/discuss/889001/C%2B%2B-quadratic...-linearithmic...-linear!
//Runtime: 148 ms, faster than 50.00% of C++ online submissions for Maximal Network Rank.
//Memory Usage: 33.3 MB, less than 50.00% of C++ online submissions for Maximal Network Rank.
class Solution {
public:
    int encode(int i, int j){
        if(i > j) swap(i, j);
        //n's range [2,100]
        //i*128+j
        return (i<<7)+j;
    }
    
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        vector<int> degrees(n, 0);
        unordered_set<int> edges;
        
        for(vector<int>& road : roads){
            edges.insert(encode(road[0], road[1]));
            ++degrees[road[0]];
            ++degrees[road[1]];
        }
        
        vector<int> indices(n);
        iota(indices.begin(), indices.end(), 0);
        //the index whose degree is larger is put former
        sort(indices.begin(), indices.end(), [&degrees](int i, int j){return degrees[i] > degrees[j];});
        
        size_t ans = 0;
        bool stop = false;
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                if(degrees[indices[i]] + degrees[indices[j]] < ans){
                    stop = true;
                    break;
                }
                ans = max(ans, degrees[indices[i]] + degrees[indices[j]] - edges.count(encode(indices[i], indices[j])));
            }
            if(stop) break;
        }
        
        return ans;
    }
};

//O(N)
//https://leetcode.com/problems/maximal-network-rank/discuss/889001/C%2B%2B-quadratic...-linearithmic...-linear!
//Runtime: 152 ms, faster than 50.00% of C++ online submissions for Maximal Network Rank.
//Memory Usage: 33.2 MB, less than 50.00% of C++ online submissions for Maximal Network Rank.
class Solution {
public:
    int encode(int i, int j){
        if(i > j) swap(i, j);
        //n's range [2,100]
        //i*128+j
        return (i<<7)+j;
    }
    
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        vector<int> degrees(n, 0);
        unordered_set<int> edges;
        
        for(vector<int>& road : roads){
            edges.insert(encode(road[0], road[1]));
            ++degrees[road[0]];
            ++degrees[road[1]];
        }
        
        int max_i = max_element(degrees.begin(), degrees.end()) - degrees.begin();
        int max_degree = degrees[max_i];
        int max_degree_count = count(degrees.begin(), degrees.end(), max_degree);
        
        size_t ans = 0;
        
        if(max_degree_count == 1){
            //there are only one city with max degree
            //try all other cities
            for(int j = 0; j < n; ++j){
                if(j == max_i) continue;
                ans = max(ans, max_degree+degrees[j]-edges.count(encode(max_i, j)));
            }
        }else{
            //there are multiple cities with max degree
            //if these cities are fully connected, then ans is max_degree * 2 - 1
            //otherwise we can find two such cities which are not directly connected, so  ans is max_degree * 2
            int roads_btw_max_degree = count_if(roads.begin(), roads.end(),
                [&degrees, &max_degree](vector<int>& r){
                    return (degrees[r[0]] == max_degree) && (degrees[r[1]] == max_degree);});
            ans = max_degree * 2 - (roads_btw_max_degree == max_degree_count*(max_degree_count-1)/2);
        }
        
        return ans;
    }
};
