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

//DFS
//Runtime: 1564 ms, faster than 40.21% of C++ online submissions for Number of Nodes in the Sub-Tree With the Same Label.
//Memory Usage: 290.5 MB, less than 100.00% of C++ online submissions for Number of Nodes in the Sub-Tree With the Same Label.
class Solution {
public:
    vector<int> dfs(vector<vector<int>>& tree, string& labels, int cur, vector<int>& ans){
        vector<int> counter(26, 0);
        counter[labels[cur]-'a'] = 1;
        
        for(int nei : tree[cur]){
            vector<int> subcounter = dfs(tree, labels, nei, ans);
            for(int i = 0; i < counter.size(); ++i){
                counter[i] += subcounter[i];
            }
        }
        //since we are using dfs, now counter's coverage is the subtree rooted at cur
        ans[cur] += counter[labels[cur]-'a'];
        
        return counter;
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
        
        vector<int> ans(n);
        
        dfs(tree, labels, 0, ans);
        
        return ans;
    }
};

//DFS, visited
//https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/discuss/743133/JavaPython-3-DFS-w-brief-explanation-and-analysis.
//Runtime: 1084 ms, faster than 80.42% of C++ online submissions for Number of Nodes in the Sub-Tree With the Same Label.
//Memory Usage: 289.1 MB, less than 100.00% of C++ online submissions for Number of Nodes in the Sub-Tree With the Same Label.
//time: O(N), space: O(N)
class Solution {
public:
    vector<int> dfs(vector<vector<int>>& adjList, string& labels, vector<bool>& visited, int cur, vector<int>& ans){
        vector<int> counter(26, 0);
        counter[labels[cur]-'a'] = 1;
        
        for(int nei : adjList[cur]){
            if(!visited[nei]){
                visited[nei] = true;
                vector<int> subcounter = dfs(adjList, labels, visited, nei, ans);
                for(int i = 0; i < counter.size(); ++i){
                    counter[i] += subcounter[i];
                }
            }
        }
        //since we are using dfs, now counter's coverage is the subtree rooted at cur
        ans[cur] += counter[labels[cur]-'a'];
        
        return counter;
    };
    
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        vector<vector<int>> adjList(n);
        vector<vector<int>> counter(n, vector<int>(26, -1));
        
        //bi-directional
        for(vector<int>& edge : edges){
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }
        
        vector<int> ans(n);
        vector<bool> visited(n, false);
        
        visited[0] = true;
        dfs(adjList, labels, visited, 0, ans);
        
        return ans;
    }
};

//DFS, remove "visited"
//https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/discuss/743133/JavaPython-3-DFS-w-brief-explanation-and-analysis.
//Runtime: 1476 ms, faster than 49.89% of C++ online submissions for Number of Nodes in the Sub-Tree With the Same Label.
//Memory Usage: 278.8 MB, less than 100.00% of C++ online submissions for Number of Nodes in the Sub-Tree With the Same Label.
//time: O(N), space: O(N)
class Solution {
public:
    vector<int> dfs(vector<vector<int>>& adjList, string& labels, int parent, int cur, vector<int>& ans){
        vector<int> counter(26, 0);
        char c = labels[cur]-'a';
        counter[c] = 1;
        
        for(int nei : adjList[cur]){
            if(nei != parent){
                vector<int> subcounter = dfs(adjList, labels, cur, nei, ans);
                for(int i = 0; i < counter.size(); ++i){
                    counter[i] += subcounter[i];
                }
            }
        }
        //since we are using dfs, now counter's coverage is the subtree rooted at cur
        ans[cur] = counter[c];
        
        return counter;
    };
    
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        vector<vector<int>> adjList(n);
        vector<vector<int>> counter(n, vector<int>(26, -1));
        
        //bi-directional
        for(vector<int>& edge : edges){
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }
        
        vector<int> ans(n, 0);
        int parent = -1;
        
        dfs(adjList, labels, -1, 0, ans);
        
        return ans;
    }
};
