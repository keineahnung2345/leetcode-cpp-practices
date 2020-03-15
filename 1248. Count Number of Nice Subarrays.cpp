//TLE
//23 / 38 test cases passed.
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int left = 0, right = 0;
        int ans = 0;
        
        for(; left < nums.size(); left++){
            int odds = 0;
            right = left;
            while(odds < k && right < nums.size()){
                if(nums[right]%2 == 1){
                    odds++;
                }
                // cout << left << right << odds << endl;
                right++;
            }
            right--;
            // cout << left << right << odds << endl;
            
            //if right is valid, then we've found a nice sub-array
            if(right < nums.size() && odds == k){
                ans++;
                // cout << left << right << odds << ans << endl;
                
                //remaining nice subarray starting from "left"
                right++;
                while(right < nums.size() && nums[right]%2 == 0){
                    ans++;
                    // cout << left << right << odds << ans << endl;
                    right++;
                }
            }
        }
        
        return ans;
    }
};

//Runtime: 200 ms, faster than 37.86% of C++ online submissions for Count Number of Nice Subarrays.
//Memory Usage: 16.1 MB, less than 100.00% of C++ online submissions for Count Number of Nice Subarrays.
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int left = 0, right = 0;
        int ans = 0;
        int odds = 0;
        
        for(; left < nums.size(); left++){
            //sliding window
            if(left > 0 && nums[left-1]%2 == 1){
                odds--;
            }
            //if left == 0, it's first time
            //o.w., it's not first time and nums[right] has been considered
            //so here use "right++" to skip nums[right]
            if(left > 0){
                right++;
            }
            while(odds < k && right < nums.size()){
                if(nums[right]%2 == 1){
                    odds++;
                }
                // cout << left << right << odds << endl;
                right++;
            }
            right--;
            // cout << left << right << odds << endl;
            
            //if right is valid, then we've found a nice sub-array
            if(right < nums.size() && odds == k){
                ans++;
                // cout << left << right << odds << ans << endl;
                
                //remaining nice subarray starting from "left"
                int head = right;
                vector<int>::iterator it = find_if(nums.begin()+head+1,
                    nums.end(), 
                    [](int e){return e%2 == 1;});
                //remaining valid head's value: [head+1, it-1]
                ans += (it-1 - (nums.begin()+head));
                // cout << left << head << odds << ans << endl;
            }
        }
        
        return ans;
    }
};

//https://leetcode.com/problems/count-number-of-nice-subarrays/discuss/508217/C%2B%2B%3A-Visual-explanation.-O(1)-space.-Two-pointers
//Runtime: 172 ms, faster than 95.48% of C++ online submissions for Count Number of Nice Subarrays.
//Memory Usage: 15.7 MB, less than 100.00% of C++ online submissions for Count Number of Nice Subarrays.
//time: O(n), space: O(1)
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int left = 0, odds = 0, count = 0, ans = 0;
        for(int right = 0; right < nums.size(); right++){
            if(nums[right] % 2 == 1){
                odds++;
                if(odds >= k){
                    count = 1;
                    //move left bound while counting
                    while(nums[left++] % 2 == 0){
                        count++;
                    }
                    ans += count;
                }
            }else if(odds >= k){
                //we already have "count" subarrays of [left, last right with odd number]
                //now right points to an even number, we get "count" subarrays of [left, right]
                ans += count;
            }
            // cout << "[" << left << ", " << right << "]: " << odds << ", " << count << ", " << ans << endl;
        }
        return ans;
    }
};
