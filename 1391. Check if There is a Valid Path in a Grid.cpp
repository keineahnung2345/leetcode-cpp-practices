//Graph
//Runtime: 428 ms, faster than 27.27% of C++ online submissions for Check if There is a Valid Path in a Grid.
//Memory Usage: 72 MB, less than 100.00% of C++ online submissions for Check if There is a Valid Path in a Grid.
class Solution {
public:
    vector<vector<bool>> visited;
    vector<vector<int>> grid;
    vector<int> right;
    vector<int> left;
    vector<int> up;
    vector<int> down;
    int m, n;
    
    bool leftValid(int i, int j){
        if(j >= 0 && !visited[i][j] && find(right.begin(), right.end(), grid[i][j]) != right.end())
            return true;
        return false;
    };
    
    bool rightValid(int i, int j){
        if(j < n && !visited[i][j] && find(left.begin(), left.end(), grid[i][j]) != left.end())
            return true;
        return false;
    };
    
    bool upValid(int i, int j){
        if(i >= 0 && !visited[i][j] && find(down.begin(), down.end(), grid[i][j]) != down.end())
            return true;
        return false;
    };
    
    bool downValid(int i, int j){
        // cout << "downValid: " << i+1 << " " << j << 
        if(i < m && !visited[i][j] && find(up.begin(), up.end(), grid[i][j]) != up.end())
            return true;
        return false;
    };
    
    bool hasValidPath(vector<vector<int>>& grid) {
        this->grid = grid;
        this->m = grid.size();
        this->n = grid[0].size();
        visited = vector<vector<bool>>(this->m, vector<bool>(this->n, false));
        
        //can connect to which direction
        // int tmp[3] = {1,4,6};
        right = {1,4,6};
        // right.assign(&tmp[0], &tmp[0]+3);
        left = {1,3,5};
        up = {2,5,6};
        down = {2,3,4};
        
        queue<vector<int>> q;
        
        q.push({0,0});
        
        while(!q.empty()){
            vector<int> cur = q.front(); q.pop();
            int i = cur[0], j = cur[1];
            // cout << i << " " << j << endl;
            visited[i][j] = true;
            
            //we have reached the goal!
            if(i == m-1 && j == n-1) return true;
            
            switch(grid[i][j]){
                case 1:
                    //left
                    if(leftValid(i, j-1)){
                        q.push({i, j-1});
                    }
                    //right
                    if(rightValid(i, j+1)){
                        q.push({i, j+1});
                    }
                    break;
                case 2:
                    //up
                    if(upValid(i-1, j)){
                        q.push({i-1, j});
                    }
                    //down
                    if(downValid(i+1, j)){
                        q.push({i+1, j});
                    }
                    break;
                case 3:
                    //left
                    if(leftValid(i, j-1)){
                        q.push({i, j-1});
                    }
                    //down
                    if(downValid(i+1, j)){
                        q.push({i+1, j});
                    }
                    break;
                case 4:
                    //right
                    if(rightValid(i, j+1)){
                        q.push({i, j+1});
                    }
                    //down
                    if(downValid(i+1, j)){
                        q.push({i+1, j});
                    }
                    break;
                case 5:
                    //up
                    if(upValid(i-1, j)){
                        q.push({i-1, j});
                    }
                    //left
                    if(leftValid(i, j-1)){
                        q.push({i, j-1});
                    }
                    break;
                case 6:
                    //up
                    if(upValid(i-1, j)){
                        q.push({i-1, j});
                    }
                    //right
                    if(rightValid(i, j+1)){
                        q.push({i, j+1});
                    }
                    break;
            }
        }
        
        return false;
    }
};
