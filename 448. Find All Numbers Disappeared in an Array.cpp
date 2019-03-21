/**
Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements of [1, n] inclusive that do not appear in this array.

Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

Example:

Input:
[4,3,2,7,8,2,3,1]

Output:
[5,6]
**/

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        //Method 1(TLE)
        /**
        if(nums.size()==0){
            return vector<int>();
        }
        int _min = nums[0], _max = nums[0];
        vector<int> ans;
        for(int num : nums){
            if(num < _min){
                for(int i = num+1; i < _min; i++){
                    ans.push_back(i);
                }
                _min = num;
            }
            
            if(num > _max){
                for(int i = _max+1; i < num; i++){
                    ans.push_back(i);
                }
                _max = num;
            }
            
            vector<int>::iterator it = find(ans.begin(), ans.end(), num);
            if(it!=ans.end()){
                ans.erase(it);
            }
        }
        **/
        
        //Method 2(TLE)
        /**
        if(nums.size()==0){
            return vector<int>();
        }
        //if nums' values won't cover the range of [1,n]
        for(int i = 1; i < _min; i++){
            ans.push_back(i);
        }
        
        for(int i = nums.size(); i > _max; i--){
            ans.push_back(i);
        }
        
        vector<int> ans(nums.size());
        iota(ans.begin(), ans.end(), 1); //1 is the starting number
        
        for(int num : nums){
            ans.erase(remove(ans.begin(), ans.end(), num), ans.end());
        }
        **/
        
        //Method 3
        if(nums.size()==0){
            return vector<int>();
        }
        
        vector<bool> exist(nums.size(), false);
        for(int num : nums){
            exist[num-1] = true;
        }
        
        vector<int> ans;
        for(int i = 0; i < nums.size(); i++){
            if(exist[i]==false){
                ans.push_back(i+1);
            }
        }
        
        return ans;
    }
};
