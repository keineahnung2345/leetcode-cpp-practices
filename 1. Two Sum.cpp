//Runtime: 8 ms, faster than 99.93% of C++ online submissions for Two Sum.
//Memory Usage: 9.5 MB, less than 70.01% of C++ online submissions for Two Sum.

class Solution {
public:
    template <typename T>
    vector<int> sort_indexes(const vector<T> &v) {

      // initialize original index locations
      vector<int> idx(v.size());
      iota(idx.begin(), idx.end(), 0);

      // sort indexes based on comparing values in v
      sort(idx.begin(), idx.end(),
           [&v](int i1, int i2) {return v[i1] < v[i2];});

      return idx;
    }
    
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ixs = sort_indexes(nums);
        
        int i = 0, j = nums.size()-1;
        
        while(i < j){
            int ix1 = ixs[i], ix2 = ixs[j];
            if(nums[ix1] + nums[ix2] == target){
                return vector<int> {ix1, ix2};
            }else if(nums[ix1] + nums[ix2] < target){
                i++;
            }else{
                j--;
            }
        }
        return vector<int>();
    }
};

/**
Approach 1: Brute Force
**/

/**
Complexity Analysis

Time complexity : O(n^2). 
For each element, 
we try to find its complement by looping through the rest of array which takes O(n) time. 
Therefore, the time complexity is O(n^2).
Space complexity : O(1). 
**/

/**
Approach 2: Two-pass Hash Table
build map and then check for each key whether its complement exists
**/

/**
Complexity Analysis:
Time complexity : O(n). 
We traverse the list containing nn elements exactly twice. 
Since the hash table reduces the look up time to O(1), the time complexity is O(n).
Space complexity : O(n). 
The extra space required depends on the number of items stored in the hash table, which stores exactly nn elements. 
**/

/**
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> ixs;
        for(int i = 0; i < nums.size(); i++){
            ixs[nums[i]] = i;
        }
        
        for(int i = 0; i < nums.size(); i++){
            int complement = target - nums[i];
            if(ixs.find(complement) != ixs.end() && ixs[complement] != i){
                return vector<int> {i, ixs[complement]};
            }
        }
        
        return vector<int> {};
    }
};
**/

/**
Approach 3: One-pass Hash Table
build and check for complement at the same time
**/

/**
Complexity Analysis:
Time complexity : O(n).
We traverse the list containing nn elements only once. 
Each look up in the table costs only O(1) time.
Space complexity : O(n). 
The extra space required depends on the number of items stored in the hash table, which stores at most nn elements.
**/

/**
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> ixs;
        for(int i = 0; i < nums.size(); i++){
            int complement = target - nums[i];
            if(ixs.find(complement) != ixs.end()){
                return vector<int> {i, ixs[complement]};
            }
            ixs[nums[i]] = i;
        }
        return vector<int> {};
    }
};
**/
