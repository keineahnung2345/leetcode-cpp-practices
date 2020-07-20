//TLE
//59 / 59 test cases passed, but took too long.
class Solution {
public:
    int dfs(vector<vector<int>>& adjList, string& labels, int cur, char c, vector<vector<int>>& counter){
        // cout << "cur: " << cur << ", c: " << c << endl;
        if(counter[cur][c-'a'] != -1){
            return counter[cur][c-'a'];
        }
        
        int count = (labels[cur] == c);
        
        for(int nei : adjList[cur]){
            count += dfs(adjList, labels, nei, c, counter);
        }
        
        return counter[cur][c-'a'] = count;
    };
    
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        vector<vector<int>> adjList(n);
        vector<vector<int>> counter(n, vector<int>(26, -1));
        
        //bi-directional
        for(vector<int>& edge : edges){
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }
        
        vector<bool> visited(n, false);
        //one directional, top-down
        vector<vector<int>> tree(n);
        
        stack<int> stk;
        stk.push(0);
        visited[0] = true;
        
        while(!stk.empty()){
            int cur = stk.top(); stk.pop();
            
            for(int nei : adjList[cur]){
                if(!visited[nei]){
                    visited[nei] = true;
                    tree[cur].push_back(nei);
                    stk.push(nei);
                }
            }
        }
        
        // for(int i = 0; i < n; ++i){
        //     cout << i << " : ";
        //     for(int child : tree[i]) cout << child << " ";
        //     cout << endl;
        // }
        
        for(int i = 0; i < n; ++i){
            dfs(tree, labels, i, labels[i], counter);
        }
        
        vector<int> ans(n);
        
        for(int i = 0; i < n; ++i){
            ans[i] = counter[i][labels[i]-'a'];
        }
        
        return ans;
    }
};
