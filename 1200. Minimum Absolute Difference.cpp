//Runtime: 120 ms, faster than 60.62% of C++ online submissions for Minimum Absolute Difference.
//Memory Usage: 17 MB, less than 100.00% of C++ online submissions for Minimum Absolute Difference.

class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        
        int dist = INT_MAX;
        vector<vector<int>> ans;
        
        for(int i = 0; i < arr.size() - 1; i++){
            if(arr[i+1] - arr[i] < dist){
                dist = arr[i+1] - arr[i];
                ans.clear();
                ans.push_back({arr[i], arr[i+1]});
            }else if(arr[i+1] - arr[i] == dist){
                ans.push_back({arr[i], arr[i+1]});
            }
        }
        
        return ans;
    }
};
