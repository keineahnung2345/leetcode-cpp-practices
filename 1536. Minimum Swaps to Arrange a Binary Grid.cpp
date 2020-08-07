//WA
//104 / 129 test cases passed.
//[[1,0,0,0,0,0],[0,1,0,1,0,0],[1,0,0,0,0,0],[1,1,1,0,0,0],[1,1,0,1,0,0],[1,0,0,0,0,0]]
class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        
        vector<pair<int, int>> maxRight(n);
        
        for(int i = 0; i < n; ++i){
            int j;
            for(j = n-1; j >= 0 && grid[i][j] == 0; --j){}
            maxRight[i] = {n-1-j, i};
        }
        
        /*
        sort descending by count and then ascending by index
        [[1,0,0,0],[1,1,1,1],[1,0,0,0],[1,0,0,0]]
        */
        sort(maxRight.begin(), maxRight.end(),
            [](pair<int,int>& a, pair<int,int>& b){
                return (a.first == b.first) ? a.second < b.second : a.first > b.first;
            });
        for(int i = 0; i < n; ++i){
            if(maxRight[i].first < n-1-i) return -1;
        }
        
        //now we are sure that the answer exist
        int swaps = 0;
        
        for(int i = 0; i < n; ++i){
            swaps += maxRight[i].second - i;
            for(int j = i+1; j < n; ++j){
                if(maxRight[j].second < maxRight[i].second){
                    ++maxRight[j].second;
                }
            }
        }
        
        return swaps;
    }
};
