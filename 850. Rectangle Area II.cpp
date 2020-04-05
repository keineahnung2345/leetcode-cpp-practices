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
