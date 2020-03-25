//Runtime: 20 ms, faster than 84.43% of C++ online submissions for Friend Circles.
//Memory Usage: 8.7 MB, less than 100.00% of C++ online submissions for Friend Circles.
class DSU{
public:
    vector<int> parent;
    
    DSU(int N){
        parent = vector<int>(N);
        //every node's parent is itself initially
        iota(parent.begin(), parent.end(), 0);
    };
    
    int find(int x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y){
        parent[find(x)] = find(y);
    }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        
        DSU dsu(n);
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                if(M[i][j]){
                    // cout << i << " " << j << "|";
                    dsu.unite(i, j);
                }
            }
        }
        // cout << endl;
        
        set<int> uniqParent;
        
        for(int i = 0; i < n; i++){
            //we should not use dsu.parent[i] but dsu.find(i) here!
            // uniqParent.insert(dsu.parent[i]);
            uniqParent.insert(dsu.find(i));
            // cout << i << "'s parent: " << dsu.parent[i] << endl;
        }
        
        return uniqParent.size();
    }
};
