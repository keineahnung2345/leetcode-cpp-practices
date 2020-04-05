//Approach #1: Principle of Inclusion-Exclusion
//TLE
//46 / 76 test cases passed.
//time: O(N*2^N), space: O(N)
class Solution {
public:
    vector<int> intersect(vector<int>& rec1, vector<int>& rec2){
        //the returned rectangle will have negative side if the two input rectangles have no intersection
        return {max(rec1[0], rec2[0]),
               max(rec1[1], rec2[1]),
               min(rec1[2], rec2[2]),
               min(rec1[3], rec2[3])};
    };
    
    long area(vector<int>& rec){
        long dx = max(rec[2] - rec[0], 0);
        long dy = max(rec[3] - rec[1], 0);
        return dx*dy;
    }
    
    int rectangleArea(vector<vector<int>>& rectangles) {
        int n = rectangles.size();
        
        long ans = 0;
        for(int subset = 1; subset < (1<<n); subset++){
            //subset from 0001 to 1111
            //maximum possible rectangle
            vector<int> rec = {0, 0, (int)1e9, (int)1e9};
            int parity = -1;
            //inspect the subset, start from least significant bit
            for(int bit = 0; bit < n; bit++){
                if((subset>>bit) & 1){
                    rec = intersect(rec, rectangles[bit]);
                    parity *= -1;
                }
            }
            /*
            if there are odd set bits, parity is 1
            otherwise parity is -1
            */
            ans += parity * area(rec);
        }
        
        long mod = 1e9+7;
        ans %= mod;
        
        //?
        if(ans < 0) ans += mod;
        return ans;
    }
};

//Approach #2: Coordinate Compression
//Runtime: 196 ms, faster than 6.10% of C++ online submissions for Rectangle Area II.
//Memory Usage: 8.3 MB, less than 100.00% of C++ online submissions for Rectangle Area II.
//time: O(N^3), space: O(N^2)
class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int n = rectangles.size();
        set<int> xvals, yvals;
        
        for(vector<int>& rec : rectangles){
            xvals.insert(rec[0]);
            yvals.insert(rec[1]);
            xvals.insert(rec[2]);
            yvals.insert(rec[3]);
        }
        
        vector<int> imapx(xvals.begin(), xvals.end());
        vector<int> imapy(yvals.begin(), yvals.end());
        sort(imapx.begin(), imapx.end());
        sort(imapy.begin(), imapy.end());
        
        map<int, int> mapx, mapy;
        // cout << "imapx: " << endl;
        for(int i = 0; i < imapx.size(); i++){
            mapx[imapx[i]] = i;
            // cout << i << " " << imapx[i] << endl;
        }
        // cout << "imapy: " << endl;
        for(int i = 0; i < imapy.size(); i++){
            mapy[imapy[i]] = i;
            // cout << i << " " << imapy[i] << endl;
        }
        
        vector<vector<bool>> grid = vector(imapx.size(), vector(imapy.size(), false));
        for(vector<int>& rec : rectangles){
            //fill the corresponding grids
            for(int x = mapx[rec[0]]; x < mapx[rec[2]]; x++){
                for(int y = mapy[rec[1]]; y < mapy[rec[3]]; y++){
                    grid[x][y] = true;
                }
            }
        }
        
        long ans = 0;
        
        for(int x = 0; x < grid.size(); x++){
            for(int y = 0; y < grid[0].size(); y++){
                if(grid[x][y]){
                    ans += (long)(imapx[x+1] - imapx[x]) * (imapy[y+1] - imapy[y]) % ((int)1e9+7);
                    ans %= ((int)1e9+7);
                }
            }
        }
        
        ans %= ((int)1e9+7);
        
        return ans;
    }
};
