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
                //starts from position with higher minhp
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
