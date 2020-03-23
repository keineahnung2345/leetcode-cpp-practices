//map
//Runtime: 420 ms, faster than 39.39% of C++ online submissions for Cinema Seat Allocation.
//Memory Usage: 76 MB, less than 100.00% of C++ online submissions for Cinema Seat Allocation.
//unordered_map
//Runtime: 380 ms, faster than 44.97% of C++ online submissions for Cinema Seat Allocation.
//Memory Usage: 75.1 MB, less than 100.00% of C++ online submissions for Cinema Seat Allocation.
class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        int ans = 0;
        
        // sort(reservedSeats.begin(), reservedSeats.end());
        
        map<int, set<int>> rows;
        
        for(vector<int>& seat : reservedSeats){
            // cout << seat[0] << " " << seat[1] << " | ";
            if(seat[1] != 1 && seat[1] != 10)
                rows[seat[0]].insert(seat[1]);
        }
        // cout << endl;
        
        set<int> left = {2,3,4,5};
        set<int> middle = {4,5,6,7};
        set<int> right = {6,7,8,9};
        
        ans += (n - rows.size())*2;
        
        for(auto it = rows.begin(); it != rows.end(); it++){
            int i = it->first;
            set<int> row = it->second;
            set<int> result;

            bool filled = false;

            set_intersection(left.begin(), left.end(), row.begin(), row.end(), inserter(result, result.begin()));
            if(result.size() == 0){
                ans++;
                filled = true;
            }
            result.clear();

            set_intersection(right.begin(), right.end(), row.begin(), row.end(), inserter(result, result.begin()));
            if(result.size() == 0){
                ans++;
                filled = true;
            }
            result.clear();

            if(!filled){
                set_intersection(middle.begin(), middle.end(), row.begin(), row.end(), inserter(result, result.begin()));
                if(result.size() == 0){
                    ans++;
                    filled = true;
                }
                result.clear();
            }
        }
        
        return ans;
    }
};
