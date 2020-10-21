//WA
//57 / 66 test cases passed.
//indirectly connection also considered true?
class Solution {
public:
    int gcd(int x, int y){
        if(y == 0) return x;
        return gcd(y, x%y);
    }
    
    int encode(int& i, int& j, int& n){
        return i*(n+1)+j;
    }
    
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
        int m = queries.size();
        vector<bool> ans(m, true);
        
        if(threshold == 0){
            return ans;
        }
        
        unordered_set<int> edges;
        
        for(int i = 1; i <= n; ++i){
            for(int j = i+1; j <= n; ++j){
                if(gcd(i, j) > threshold){
                    edges.insert(encode(i, j, n));
                }
            }
        }
        
        for(int i = 0; i < m; ++i){
            vector<int>& q = queries[i];
            if(q[0] > q[1]) swap(q[0], q[1]);
            
            ans[i] = (edges.find(encode(q[0], q[1], n)) != edges.end());
        }
        
        return ans;
    }
};
