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

//Approach 3: Using Cyclic Replacements
//Runtime: 8 ms, faster than 88.24% of C++ online submissions for Rotate Array.
//Memory Usage: 9.9 MB, less than 70.95% of C++ online submissions for Rotate Array.
//time: O(N), space: O(1)
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        
        int count = 0;
        
        for(int start = 0; count < n; ++start){
            int cur = start;
            //temporarily store the value k position before nums[next]
            int prev = nums[cur];
            do{
                int next = (cur+k) % n;
                // cout << "nums[" << next << "]: " << prev << endl;
                swap(nums[next], prev);
                cur = next;
                ++count;
            }while(cur != start);
        }
    }
};
