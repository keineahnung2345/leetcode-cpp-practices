//DFS, iterative
//WA(because the visit order of children matters)
//68 / 138 test cases passed.
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if(m == 0) return 0;
        int n = matrix[0].size();
        if(n == 0) return 0;
        
        vector<vector<int>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        
        int ans = 0;
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                vector<vector<bool>> visited(m, vector(n, false));
                stack<vector<int>> stk;
                
                visited[i][j] = true;
                stk.push({i, j, 1});
                
                while(!stk.empty()){
                    vector<int> cur = stk.top(); stk.pop();
                    int ci = cur[0], cj = cur[1], cd = cur[2];
                    
                    ans = max(ans, cd);
                    
                    for(vector<int>& dir : dirs){
                        int ni = ci+dir[0];
                        int nj = cj+dir[1];
                        
                        if(ni >= 0 && ni < m && nj >= 0 && nj < n){
                            if(!visited[ni][nj] && matrix[ni][nj] > matrix[ci][cj]){
                                visited[ni][nj] = true;
                                //depth plus 1
                                stk.push({ni, nj, cd+1});
                            }
                        }
                    }
                }
            }
        }
        
        return ans;
    }
};

//DFS, recursive, memorization
//https://leetcode.com/problems/longest-increasing-path-in-a-matrix/discuss/78308/15ms-Concise-Java-Solution
//Runtime: 56 ms, faster than 39.66% of C++ online submissions for Longest Increasing Path in a Matrix.
//Memory Usage: 12.6 MB, less than 90.91% of C++ online submissions for Longest Increasing Path in a Matrix.
class Solution {
public:
    //the longest path starting from i, j
    vector<vector<int>> cache;
    vector<vector<int>> dirs;
    vector<vector<int>> matrix;
    int m, n;
    
    int dfs(int i, int j){
        if(cache[i][j] != 0) return cache[i][j];
        
        int maxLen = 1;

        for(vector<int>& dir : dirs){
            int ni = i+dir[0];
            int nj = j+dir[1];

            if(ni >= 0 && ni < m && nj >= 0 && nj < n && matrix[ni][nj] > matrix[i][j]){
                int curLen = 1 + dfs(ni, nj);
                //try all 4 directions and choose the best one
                maxLen = max(maxLen, curLen);
            }
        }
        
        cache[i][j] = maxLen;
        
        return maxLen;
    }
    
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        this->m = matrix.size();
        if(m == 0) return 0;
        this->n = matrix[0].size();
        if(n == 0) return 0;
        
        this->matrix = matrix;
        cache = vector<vector<int>>(m, vector<int>(n, 0));
        dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        
        int ans = 0;
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                ans = max(ans, dfs(i, j));
            }
        }
        
        return ans;
    }
};

//BFS, Topological Sort
//https://leetcode.com/problems/longest-increasing-path-in-a-matrix/discuss/288520/BFS-Implemented-Topological-Sort
//Runtime: 168 ms, faster than 18.07% of C++ online submissions for Longest Increasing Path in a Matrix.
//Memory Usage: 27.9 MB, less than 9.09% of C++ online submissions for Longest Increasing Path in a Matrix.
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if(m == 0) return 0;
        int n = matrix[0].size();
        if(n == 0) return 0;
        
        vector<vector<int>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        
        vector<vector<int>> inDegree(m, vector(n, 0));
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                for(vector<int>& dir : dirs){
                    int ni = i + dir[0];
                    int nj = j + dir[1];
                    if(ni >= 0 && ni < m && nj >= 0 && nj < n && matrix[i][j] < matrix[ni][nj]){
                        //we create an edge from smaller to larger
                        inDegree[ni][nj]++;
                    }
                }
            }
        }
        
        queue<vector<int>> q;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(inDegree[i][j] == 0){
                    q.push({i, j});
                }
            }
        }
        
        int ans = 0;
        
        while(!q.empty()){
            int levelCount = q.size();
            //visite current level
            while(levelCount-- > 0){
                vector<int> cur = q.front(); q.pop();
                int ci = cur[0], cj = cur[1];

                for(vector<int>& dir : dirs){
                    int ni = ci+dir[0];
                    int nj = cj+dir[1];

                    if(ni >= 0 && ni < m && nj >= 0 && nj < n && matrix[ni][nj] > matrix[ci][cj] && --inDegree[ni][nj] == 0){
                        //if there's an edge from (ci,cj) to (ni,nj)
                        q.push({ni, nj});
                    }
                }
            }
            ans++;
        }
        
        return ans;
    }
};
