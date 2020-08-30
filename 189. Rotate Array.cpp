//Naive solution, using extra array
//Runtime: 4 ms, faster than 99.57% of C++ online submissions for Rotate Array.
//Memory Usage: 10.1 MB, less than 22.54% of C++ online submissions for Rotate Array.
//time: O(N), space: O(N)
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        
        vector<int> ans(n);
        
        for(int i = 0; i < n; ++i){
            ans[(i+k)%n] = nums[i];
        }
        
        for(int i = 0; i < n; ++i){
            nums[i] = ans[i];
        }
    }
};

//Approach 1: Brute Force
//time: O(N*k), space: O(1)
//TLE
//34 / 35 test cases passed.
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        
        k %= n;
        
        while(k-- > 0){
            int prev = nums[n-1];
            for(int i = 0; i < n; ++i){
                swap(nums[i], prev);
            }
            
            // for(int i = 0; i < n; ++i){
            //     cout << nums[i] << "　";
            // }
            // cout << endl;
        }
    }
};
