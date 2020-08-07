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

//https://leetcode.com/problems/find-the-winner-of-an-array-game/discuss/768007/JavaC%2B%2BPython-One-Pass-O(1)-Space
//Runtime: 268 ms, faster than 60.00% of C++ online submissions for Find the Winner of an Array Game.
//Memory Usage: 63.1 MB, less than 100.00% of C++ online submissions for Find the Winner of an Array Game.
class Solution {
public:
    int getWinner(vector<int>& arr, int k) {
        int n = arr.size();
        
        if(k >= n) return *max_element(arr.begin(), arr.end());
        
        int winner = arr[0], win_count = 0;
        for(int i = 1; i < n && win_count < k; ++i){
            if(winner < arr[i]){
                winner = arr[i];
                win_count = 0;
            }
            /*
            either the winner remains the same or changes,
            we need to increase win_count!!
            */
            ++win_count;
        }
        
        return winner;
    }
};
