//Runtime: 180 ms, faster than 65.71% of C++ online submissions for Flower Planting With No Adjacent.
//Memory Usage: 38.8 MB, less than 100.00% of C++ online submissions for Flower Planting With No Adjacent.

class Solution {
public:
    vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) {
        vector<int> ans(N);
        vector<vector<int>> graph(N);
        
        for(vector<int>& path : paths){
            int x = path[0], y = path[1];
            graph[x-1].push_back(y-1);
            graph[y-1].push_back(x-1);
        }
        
        for(int i = 0; i < N; i++){
            vector<int> colors(5); //4+1
            
            //(i, j) forms an edge
            for(int j : graph[i]){
                //ans[j] : (j+1)th graden's color index
                //this means "ans[j]"th color is used
                colors[ans[j]] = 1;
                // cout << i << "->" << j << ", " << ans[j] << endl;
            }
            
            // cout << colors[0] << " " << colors[1] << " " << colors[2] << " " << colors[3] << " " << colors[4] << endl;
            for(int c = 1; c <= 4; c++){
            // for(int c = 4; c >= 1; c--){
                // cout << c << ", " << colors[c] << endl;
                //pick the first unused color
                if(!colors[c]){
                    ans[i] = c;
                    break;
                }
            }
            // for(int i = 0; i < N; i++){
            //     cout << ans[i] << " ";
            // }
            // cout << endl;
        }

        return ans;
    }
};
