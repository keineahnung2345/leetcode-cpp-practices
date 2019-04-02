//Runtime: 152 ms, faster than 21.92% of C++ online submissions for Longest Harmonious Subsequence.
//Memory Usage: 22.4 MB, less than 28.30% of C++ online submissions for Longest Harmonious Subsequence.

/**
Approach 3: Using Sorting
**/

/**
Complexity Analysis
Time complexity : O(nlogn). Sorting takes O(nlogn) time.
Space complexity : O(logn). logn space is required by sorting in average case. 
**/

class Solution {
public:
    int findLHS(vector<int>& nums) {
        map<int, int> count;
        vector<int> key;
        
        int ans = 0;
        
        sort(nums.begin(), nums.end());
        
        for(int n : nums){
            if(count.find(n) == count.end()){
                count[n] = 1;
                key.push_back(n);
            }else{
                count[n]++;
            }
        }
        
        for(int i = 1; i < key.size(); i++){
            int k1 = key[i], k2 = key[i-1];
            if(k1 - k2 == 1) ans = max(ans, count[k1] + count[k2]);
            // cout << k1 << ", " << k2 << ", " << count[k1] << ", " << count[k2] << endl;
        }
        
        return ans;
    }
};

/**
Approach 1: Brute Force
generate all possible subsequences, and then check if they are harmonic
**/
/**
Complexity Analysis
Time complexity : O(2^n). Number of subsequences generated will be 2^n.
Space complexity : O(1)O(1). Constant space required. 
**/

//TLE

/**
class Solution {
public:
    int findLHS(vector<int>& nums) {
        int ans = 0;
        //1<<nums.size(): pow(2, nums.size())
        for(int i = 0; i < 1<<nums.size(); i++){
            int count = 0;
            int curmin = INT_MAX, curmax = INT_MIN;
            for(int j = 0; j < nums.size(); j++){
                //i&(1<<j): the jth digit of binary representation of i
                if((i&(1<<j)) != 0){
                    curmin = min(curmin, nums[j]);
                    curmax = max(curmax, nums[j]);
                    count++;
                }
            }
            if((int)((long long)curmax-(long long)curmin) == 1) ans = max(ans, count);
        }
        return ans;
    }
};
**/

/**
Approach 2: Better Brute Force
based on an element, find elements form harmonic sequence with it
**/
/**
Complexity Analysis
Time complexity : O(n^2). Two nested loops are there.
Space complexity : O(1). Constant space required. 
**/
//TLE

/**
class Solution {
public:
    int findLHS(vector<int>& nums) {
        int ans = 0;
        for(int i = 0; i < nums.size(); i++){
            int count = 0;
            bool isHarmonic = false;
            for(int j = 0; j < nums.size(); j++){
                if(nums[j] == nums[i]){
                    count++;
                }else if(nums[j] + 1 == nums[i]){
                    count++;
                    isHarmonic = true;
                }
            }
            if(isHarmonic) ans = max(ans, count);
        }
        return ans;
    }
};
**/

/**
Approach 4: Using HashMap
build map and then find continuous key
**/

/**
Complexity Analysis
Time complexity : O(n). One loop is required to fill mapmap and one for traversing the mapmap.
Space complexity : O(n). In worst case map size grows upto size nn. 
**/

/**
class Solution {
public:
    int findLHS(vector<int>& nums) {
        map<int, int> count;
        int ans = 0;
        for(int n : nums){
            if(count.find(n) == count.end()){
                count[n] = 1;
            }else{
                count[n]++;
            }
        }
        
        for(map<int, int>::iterator it = count.begin(); it != count.end(); it++){
            int k = it->first;
            if(count.find(k+1) != count.end()){
                ans = max(ans, count[k]+count[k+1]);
            }
        }
        
        return ans;
    }
};
**/

/**
Approach 5: In Single Loop
build map and check for harmonic subsequences at the same time
**/

/**
Complexity Analysis
Time complexity : O(n). Only one loop is there.
Space complexity : O(n). mapmap size grows upto size n. 
**/

//Runtime: 212 ms, faster than 6.62% of C++ online submissions for Longest Harmonious Subsequence.
//Memory Usage: 20.7 MB, less than 84.91% of C++ online submissions for Longest Harmonious Subsequence.

/**
class Solution {
public:
    int findLHS(vector<int>& nums) {
        map<int, int> count;
        int ans = 0;
        for(int n : nums){
            if(count.find(n) == count.end()){
                count[n] = 1;
            }else{
                count[n]++;
            }
            if(count.find(n+1) != count.end()){
                ans = max(ans, count[n]+count[n+1]);
            }
            if(count.find(n-1) != count.end()){
                ans = max(ans, count[n]+count[n-1]);
            }
        }
        return ans;
    }
};
**/
