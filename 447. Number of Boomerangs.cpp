//Runtime: 168 ms, faster than 97.22% of C++ online submissions for Number of Boomerangs.
//Memory Usage: 19.5 MB, less than 100.00% of C++ online submissions for Number of Boomerangs.
class Solution {
public:
    int getDist(vector<int>& a, vector<int>& b){
        // cout << a[0] << ", " << a[1] << "|" << b[0] << "," << b[1] <<  "|" << pow(a[0] - b[0], 2) + pow(a[1]-b[1],2) << endl;
        return pow(a[0]-b[0], 2) + pow(a[1]-b[1],2);
    }
    
    int P(int n, int r){
        int ans = 1;
        for(int i = n; i >= n - r + 1; i--){
            ans *= i;
        }
        return ans;
    }
    
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int n = points.size();
        vector<vector<int>> dis(n, vector<int>(n));
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j <= i; j++){
                // cout << i << ", " << j << ": " << endl;
                dis[j][i] = dis[i][j] = getDist(points[i], points[j]);
            }
        }
        
        // for(int i = 0; i < n; i++){
        //     for(int j = 0; j < n; j++){
        //         cout << dis[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        
        int ans = 0;
        
        for(int i = 0; i < n; i++){
            sort(dis[i].begin(), dis[i].end());
            // cout << "=================" << endl;
            // for(int j = 0; j < n; j++){
            //     cout << dis[i][j] << " ";
            // }
            // cout << endl;
            // cout << "=================" << endl;
            int cur = dis[i][0];
            int count = 0;
            for(int j = 0; j < n; j++){
                if(dis[i][j] == cur) count++;
                //first use count to calculate P and then update count
                if((dis[i][j] != cur || j == n-1) && count >= 2){
                    ans += P(count, 2);
                    // cout << i << ", " << j << ", " << count << ", " << P(count,2) << endl;
                }
                
                if(dis[i][j] != cur){
                    cur = dis[i][j];
                    count = 1;
                }
            }
        }
        
        return ans;
    }
};
