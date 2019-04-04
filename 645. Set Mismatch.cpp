//Runtime: 144 ms, faster than 5.63% of C++ online submissions for Set Mismatch.
//Memory Usage: 35.1 MB, less than 6.56% of C++ online submissions for Set Mismatch.

class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        multiset<int> m1(nums.begin(), nums.end());
        //if using iota, need to allocate memory for v beforehand
        vector<int> v(nums.size());
        iota(v.begin(), v.end(), 1);
        //build a multiset containing 1~N
        multiset<int> m2(v.begin(), v.end());
        
        vector<int> ans(nums.size());
        //find duplicate element first
        vector<int>::iterator it = set_difference(m1.begin(), m1.end(), m2.begin(), m2.end(), ans.begin());
        //and then find the missing element
        it = set_difference(m2.begin(), m2.end(), m1.begin(), m1.end(), ans.begin()+1);
        ans.resize(2);
        return ans;
    }
};

/**
Approach 1: Brute Force
check the occurence of 1~N in nums
**/

/**
time complexity: O(n^2)
space complexity: O(1)
**/

/**
    class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int dup = -1, missing = -1;
        for(int i = 1; i <= nums.size(); i++){
            //i from 1~N
            //count the occurence of i in nums
            int count = 0;
            for(int n : nums){
                if(n == i) count++;
            }
            if(count == 2) dup = i;
            if(count == 0) missing = i;
        }
        return vector<int> {dup, missing};
    }
};
**/

/**
Approach 2: Better brute Force
early stop when we've found dup and missing
**/

/**
time complexity: O(n^2)
space complexity: O(1)
**/

/**
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int dup = -1, missing = -1;
        for(int i = 1; i <= nums.size(); i++){
            //i from 1~N
            //count the occurence of i in nums
            int count = 0;
            for(int n : nums){
                if(n == i) count++;
            }
            if(count == 2) dup = i;
            if(count == 0) missing = i;
            if(dup > 0 && missing > 0) break;
        }
        return vector<int> {dup, missing};
    }
};
**/

/**
Approach 3: Using Sorting
sort and then scan to determine dup and missing
note that there are two boundary conditions when detecting missing,
so we need to initialize missing as 1 and do the following post-processing
**/

/**
time complexity: O(nlogn) sorting
space complexity: O(logn) used by sorting
**/

/**
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int dup = -1, missing = 1;
        for(int i = 1; i < nums.size(); i++){
            if(nums[i] == nums[i-1]) dup = nums[i];
            //this line can only detect missing when missing is not 1 or N
            //[1,2,2,4]: 4>2+1
            //[2,3,3,4,5,6]: 1 can't be detected as missing, so we initialize missing as 1
            //[1,2,3,3]: 4 can't be detected as missing, so later we check if nums[nums.size()-1] equals to nums.size()
            else if(nums[i] > nums[i-1]+1) missing = nums[i-1]+1;
        }
        return vector<int> {dup, nums[nums.size()-1] != nums.size() ? nums.size() : missing};
    }
};
**/

/**
Approach 4: Using Map
record the count of elements in nums in a map
**/

/**
time complexity: O(n)
space complexity: O(n)
**/

//Runtime: 148 ms, faster than 5.63% of C++ online submissions for Set Mismatch.
//Memory Usage: 21.8 MB, less than 11.48% of C++ online submissions for Set Mismatch.

/**class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        map<int, int> count;
        int dup = -1, missing = -1;
        for(int n : nums){
            if(count.find(n) == count.end()){
                count[n] = 1;
            }else{
                count[n]++;
            }
        }
        for(int i = 1; i <= nums.size(); i++){
            if(count.find(i) != count.end()){
                if(count[i] == 2) dup = i;
            }else{
                missing = i;
            }
        }
        return vector<int> {dup, missing};
    }
};
**/

/**
Approach 5: Using Extra Array
use array to replace map
**/

/**
time complexity: O(n)
space complexity: O(n)
**/

//Runtime: 40 ms, faster than 70.99% of C++ online submissions for Set Mismatch.
//Memory Usage: 11.1 MB, less than 37.71% of C++ online submissions for Set Mismatch.

/**
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        vector<int> count(nums.size()+1); //count[0] is useless here
        int dup = -1, missing = -1;
        for(int i = 0; i < nums.size(); i++){
            count[nums[i]]++;
        }
        for(int i = 1; i < count.size(); i++){
            if(count[i] == 0) missing = i;
            else if(count[i] == 2) dup = i;
        }
        return vector<int> {dup, missing};
    }
};
**/

/**
Approach 6: Using Constant Space
don't maintain count anymore,
mark a element as visited by invert the corresponding element in its (index-1)
**/

/**
time complexity: O(n)
space complexity: O(n)
**/

//Runtime: 36 ms, faster than 90.00% of C++ online submissions for Set Mismatch.
//Memory Usage: 10.5 MB, less than 100.00% of C++ online submissions for Set Mismatch.

/**
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int dup = -1, missing = -1;
        for(int n : nums){
            //if n is visited, the (n-1)th element of nums will be negative
            if(nums[abs(n)-1] < 0) dup = abs(n);
            else nums[abs(n)-1] *= -1;
        }
        for(int i = 0; i < nums.size(); i++){
            //we use index n-1 to represent whether n is visited or not
            if(nums[i] > 0) missing = i+1;
        }
        return vector<int> {dup, missing};
    }
};
**/

/**
Approach 7: Using XOR
?
**/

/**
time complexity: O(n)
space complexity: O(1)
**/

//Runtime: 40 ms, faster than 70.99% of C++ online submissions for Set Mismatch.
//Memory Usage: 10.5 MB, less than 100.00% of C++ online submissions for Set Mismatch.

/**
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int xorall = 0, xor0 = 0, xor1 = 0;
        for(int n : nums) xorall ^= n;
        for(int i = 1; i <= nums.size(); i++) xorall ^= i;
        int rightmostbit = xorall & ~(xorall-1);
        for(int n : nums){
            if((n & rightmostbit) != 0){
                xor1 ^= n;
            }else{
                xor0 ^= n;
            }
        }
        for(int i = 1; i <=nums.size(); i++){
            if((i & rightmostbit) != 0){
                xor1 ^= i;
            }else{
                xor0 ^= i;
            }
        }
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] == xor0){
                return vector<int> {xor0, xor1};
            }
        }
        return vector<int> {xor1, xor0};
    }
};
**/
