//Runtime: 128 ms, faster than 100.00% of C++ online submissions for Count Unhappy Friends.
//Memory Usage: 25.8 MB, less than 75.00% of C++ online submissions for Count Unhappy Friends.
class Solution {
public:
    int unhappyFriends(int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs) {
        vector<int> p(n);
        
        for(vector<int>& pair : pairs){
            p[pair[0]] = pair[1];
            p[pair[1]] = pair[0];
        }
        
        //order: the less the more prefer, n: least prefer
        vector<vector<int>> friend2order(n, vector<int>(n, n));
        for(int i = 0; i < preferences.size(); ++i){
            for(int order = 0; order < preferences[i].size(); ++order){
                friend2order[i][preferences[i][order]] = order;
            }
        }
        
        int ans = 0;
        for(int x = 0; x < n; ++x){
            int y = p[x];
            for(int u : preferences[x]){
                if(u == y) break;
                int v = p[u];
                if(friend2order[u][x] < friend2order[u][v]){
                    ++ans;
                    break;
                }
            }
        }
        
        return ans;
    }
};
