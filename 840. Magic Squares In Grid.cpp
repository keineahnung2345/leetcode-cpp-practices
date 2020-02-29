//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Magic Squares In Grid.
//Memory Usage: 8 MB, less than 100.00% of C++ online submissions for Magic Squares In Grid.

class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        if(m < 3 || n < 3) return 0;
        vector<vector<int>> hrz(m-3+1, vector<int>(n-3+1, 0));
        vector<vector<int>> vtc(m-3+1, vector<int>(n-3+1, 0));
        //diagonal from left-top to right-bottom
        vector<vector<int>> lt(m-3+1, vector<int>(n-3+1, 0));
        //diagonal from right-top to left-bottom
        vector<vector<int>> rt(m-3+1, vector<int>(n-3+1, 0));
        int ans = 0;
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                // cout << grid[i][j] << " ";
            }
            // cout << endl;
        }
        // cout << endl;
        
        for(int i = 0; i < m-3+1; i++){
            for(int j = 0; j < n-3+1; j++){
                if(j == 0){
                    hrz[i][j] = grid[i][0]+grid[i][1]+grid[i][2];
                }else{
                    //window range: [j, j+3-1]
                    hrz[i][j] = hrz[i][j-1]+grid[i][j+3-1]-grid[i][j-1];
                }
                // cout << hrz[i][j] << " ";
            }
            // cout << endl;
        }
        // cout << endl;
        
        for(int i = 0; i < m-3+1; i++){
            for(int j = 0; j < n-3+1; j++){
                // cout << "i: " << i << ", j: " << j << endl;
                if(i == 0){
                    vtc[i][j] = grid[0][j]+grid[1][j]+grid[2][j];
                }else{
                    //window range: [i, i+3-1]
                    vtc[i][j] = vtc[i-1][j]+grid[i+3-1][j]-grid[i-1][j];
                }
                // cout << vtc[i][j] << " ";
            }
            // cout << endl;
        }
        // cout << endl;
        
        for(int i = 0; i < m-3+1; i++){
            for(int j = 0; j < n-3+1; j++){
                // cout << "i: " << i << ", j: " << j << endl;
                if(i == 0 || j == 0){
                    lt[i][j] = grid[i][j]+grid[i+1][j+1]+grid[i+2][j+2];
                }else{
                    //window range: [i, i+2] * [j, j+2]
                    lt[i][j] = lt[i-1][j-1]+grid[i+2][j+2]-grid[i-1][j-1];
                }
                // cout << lt[i][j] << " ";
            }
            // cout << endl;
        }
        // cout << endl;
        
        for(int i = 0; i < m-3+1; i++){
            for(int j = 0; j < n-3+1; j++){
                //(i,j) is the left-top corner of the magic square
                //(i,j+2) is the right-top corner
                if(i == 0 || j+2 == n-1){
                    rt[i][j] = grid[i+2][j]+grid[i+1][j+1]+grid[i][j+2];
                }else{
                    rt[i][j] = rt[i-1][j+1]+grid[i+2][j]-grid[i-1][j+3];
                }
                // cout << rt[i][j] << " ";
            }
            // cout << endl;
        }
        // cout << endl;
        
        for(int i = 0; i < m-3+1; i++){
            for(int j = 0; j < n-3+1; j++){
                int mul = 1;
                for(int x = i; x < i+3; x++){
                    for(int y = j; y < j+3; y++){
                        mul *= grid[x][y];
                    }
                }
                if(mul == 362880 && hrz[i][j] == 15 && vtc[i][j] == 15 && lt[i][j] == 15 && rt[i][j] == 15){
                    ans++;
                }
            }
        }
        
        return ans;
    }
};
