//Two pointer
//Runtime: 832 ms, faster than 5.06% of C++ online submissions for 3Sum.
//Memory Usage: 120.6 MB, less than 5.30% of C++ online submissions for 3Sum.
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int N = nums.size();
        set<vector<int>> ansSet;
        
        for(int left = 0; left <= N-3; left++){
            int mid = left+1, right = N-1;
            while(mid < right){
                if(nums[left] + nums[mid] + nums[right] == 0){
                    ansSet.insert({nums[left], nums[mid], nums[right]});
                    mid++; right--;
                }else if(nums[left] + nums[mid] + nums[right] < 0){
                    mid++;
                }else{
                    right--;
                }
            }
        }

        vector<vector<int>> ans(ansSet.begin(), ansSet.end());
        
        return ans;
    }
};

//Two pointer, optimized
//https://leetcode.com/problems/3sum/discuss/7380/Concise-O(N2)-Java-solution
//Runtime: 100 ms, faster than 69.99% of C++ online submissions for 3Sum.
//Memory Usage: 14 MB, less than 100.00% of C++ online submissions for 3Sum.
//time: O(n^2)
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int N = nums.size();
        vector<vector<int>> ans;
        
        for(int left = 0; left <= N-3; left++){
            //in this case, nums[left]'s role is already played by nums[left-1]
            //, so we will only get duplicate combinations
            if(left > 0 && nums[left] == nums[left-1]) continue;
            int mid = left+1, right = N-1;
            while(mid < right){
                if(nums[left] + nums[mid] + nums[right] == 0){
                    ans.push_back({nums[left], nums[mid], nums[right]});
                    //find a mid s.t. nums[mid+1] != current nums[mid]
                    while(mid < right && nums[mid] == nums[mid+1]) mid++;
                    while(mid < right && nums[right] == nums[right-1]) right--;
                    //switch to mid+1(nums[mid+1] != current nums[mid])
                    mid++; right--;
                }else if(nums[left] + nums[mid] + nums[right] < 0){
                    mid++;
                }else{
                    right--;
                }
            }
        }
        
        return ans;
    }
};
