//Runtime: 276 ms, faster than 50.00% of C++ online submissions for Find the Winner of an Array Game.
//Memory Usage: 63.1 MB, less than 100.00% of C++ online submissions for Find the Winner of an Array Game.
class Solution {
public:
    int getWinner(vector<int>& arr, int k) {
        int n = arr.size();
        
        if(k >= n) return *max_element(arr.begin(), arr.end());
        
        int win_count = 0;
        int max = arr[0];
        int cur = 1;
        
        while(cur < n && win_count < k){
            if(max > arr[cur]){
                ++win_count;
            }else{
                win_count = 1;
                max = arr[cur];
            }
            ++cur;
        }
        
        return max;
    }
};
