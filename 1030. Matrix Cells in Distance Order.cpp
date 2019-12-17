//Runtime: 120 ms, faster than 46.68% of C++ online submissions for Matrix Cells in Distance Order.
//Memory Usage: 26.3 MB, less than 47.50% of C++ online submissions for Matrix Cells in Distance Order.

class Solution {
public:
    //https://www.educative.io/edpresso/how-to-sort-a-map-by-value-in-cpp
    static bool val_comparator(pair<vector<int>, int>& a, pair<vector<int>, int>& b){
        return a.second < b.second;
    };
    
    vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {
        vector<pair<vector<int>, int>> distances;
        vector<vector<int>> ans;
        
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++){
                distances.push_back(make_pair(vector<int>{i, j}, abs(i-r0)+abs(j-c0)));
            }
        }
        
        sort(distances.begin(), distances.end(), val_comparator);
        
        for(vector<pair<vector<int>, int>>::iterator it = distances.begin(); it != distances.end(); it++){
            ans.push_back(it->first);
        }
        
        return ans;
    }
};
