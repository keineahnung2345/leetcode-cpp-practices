//WA
//30 / 45 test cases passed.
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        
        vector<vector<int>> hp = dungeon, minhp = dungeon;
        
        for(int row = 1; row < m; ++row){
            hp[row][0] += hp[row-1][0];
            minhp[row][0] = min(minhp[row-1][0], hp[row][0]);
        }
        
        for(int col = 1; col < n; ++col){
            hp[0][col] += hp[0][col-1];
            minhp[0][col] = min(minhp[0][col-1], hp[0][col]);
        }
        
        for(int row = 1; row < m; ++row){
            for(int col = 1; col < n; ++col){
                /*
                starts from position with higher minhp
                if minhp are the same, comes from higher hp
                but this algorithm will fail on example like:
                [[1,-3,3],
                [0,-2,0],
                [-3,-3,-3]]
                because when we are at (1,2), it will choose to
                start from (1,1), but actually start from (0,2)
                give us higher hp
                1 -2 1 
                1 -1 -1 
                -2 -4 -4 
                (hp)
                
                1 -2 -2 
                1 -1 -1 
                -2 -4 -4
                (minhp)
                */
                if(minhp[row-1][col] > minhp[row][col-1]){
                    //accumulated hp
                    hp[row][col] += hp[row-1][col];
                    //minimum hp until now
                    minhp[row][col] = min(hp[row][col], minhp[row-1][col]);
                }else if(minhp[row-1][col] < minhp[row][col-1]){
                    hp[row][col] += hp[row][col-1];
                    minhp[row][col] = min(hp[row][col], minhp[row][col-1]);
                }else if(hp[row-1][col] >= hp[row][col-1]){
                    hp[row][col] += hp[row-1][col];
                    minhp[row][col] = min(hp[row][col], minhp[row-1][col]);
                }
            }
        }
        
        for(int row = 0; row < m; ++row){
            for(int col = 0; col < n; ++col){
                cout << dungeon[row][col] << " ";
            }
            cout << endl;
        }
        
        for(int row = 0; row < m; ++row){
            for(int col = 0; col < n; ++col){
                cout << hp[row][col] << " ";
            }
            cout << endl;
        }
        
        for(int row = 0; row < m; ++row){
            for(int col = 0; col < n; ++col){
                cout << minhp[row][col] << " ";
            }
            cout << endl;
        }
        
        return (minhp[m-1][n-1] <= 0) ? (-minhp[m-1][n-1]+1) : 1;
    }
};

//DP, top-bottom(starts from right-bottom corner)
//https://leetcode.com/problems/dungeon-game/discuss/698271/Python-Short-DP-7-lines-O(mn)-top-down-explained
//Runtime: 12 ms, faster than 83.36% of C++ online submissions for Dungeon Game.
//Memory Usage: 9.2 MB, less than 13.19% of C++ online submissions for Dungeon Game.
//time: O(mn), space: O(mn)
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        
        //padding to the bottom and to the right
        vector<vector<int>> minhp(m+1, vector<int>(n+1, INT_MAX));
        
        /*
        (m,n-1) and (m-1, n) is the bottom neighbor and 
        right neighbor of princess
        */
        minhp[m][n-1] = minhp[m-1][n] = 1;
        
        for(int i = m-1; i >= 0; --i){
            for(int j = n-1; j >= 0; --j){
                if(dungeon[i][j] - min(minhp[i+1][j], minhp[i][j+1]) >= 0){
                    /*
                    we need min(minhp[i+1][j], minhp[i][j+1]) hp
                    so that we can survive if we go to (i+1,j) or (i,j+1).
                    
                    dungeon[i][j] - min(minhp[i+1][j], minhp[i][j+1]) means
                    when we are at (i,j), we get dungeon[i][j] hp,
                    and when we go to (i+1,j) or (i,j+1), 
                    we will use min(minhp[i+1][j], minhp[i][j+1]) hp
                    
                    if this number >= 0, that means we can survive at (i,j) with
                    minimum possible hp, which is 1
                    */
                    minhp[i][j] = 1;
                }else{
                    /*
                    at (i,j), our hp is dungeon[i][j],
                    (since the algorithm starts from bottom-right, 
                    we don't consider the cells before (i,j)),
                    when we go to (i+1,j) or (i,j+1),
                    we remain dungeon[i][j] - min(minhp[i+1][j], minhp[i][j+1])
                    
                    minhp[i+1][j]: we need this hp to survive at (i+1,j)
                    minhp[i][j+1]: we need this hp to survive at (i,j+1)
                    
                    min(minhp[i+1][j], minhp[i][j+1]) -dungeon[i][j]:
                    we need this hp to survive at (i,j)
                    */
                    
                    //signed integer overflow
                    // minhp[i][j] = min(minhp[i+1][j]-dungeon[i][j],
                    //                   minhp[i][j+1]-dungeon[i][j]);
                    
                    minhp[i][j] = min(minhp[i+1][j], minhp[i][j+1])-dungeon[i][j];
                }
            }
        }
        
        return minhp[0][0];
    }
};

//DP, cleaner
//https://leetcode.com/problems/dungeon-game/discuss/698271/Python-Short-DP-7-lines-O(mn)-top-down-explained
//Runtime: 12 ms, faster than 83.36% of C++ online submissions for Dungeon Game.
//Memory Usage: 9 MB, less than 55.57% of C++ online submissions for Dungeon Game.
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        
        //padding to the bottom and to the right
        vector<vector<int>> minhp(m+1, vector<int>(n+1, INT_MAX));
        
        /*
        (m,n-1) and (m-1, n) is the bottom neighbor and 
        right neighbor of princess
        */
        minhp[m][n-1] = minhp[m-1][n] = 1;
        
        for(int i = m-1; i >= 0; --i){
            for(int j = n-1; j >= 0; --j){
                minhp[i][j] = max(
                    min(minhp[i+1][j], minhp[i][j+1]) - dungeon[i][j], 
                    1);
            }
        }
        
        return minhp[0][0];
    }
};
