/**
Given a non-empty array of integers, every element appears twice except for one. Find that single one.

Note:

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Example 1:

Input: [2,2,1]
Output: 1
Example 2:

Input: [4,1,2,1,2]
Output: 4
**/

//Runtime: 36 ms, faster than 7.03% of C++ online submissions for Single Number.
//Memory Usage: 11.9 MB, less than 5.09% of C++ online submissions for Single Number.
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        map<int, int> mymap;
        
        for(int num : nums){
            if(mymap.find(num)==mymap.end()){
                mymap[num] = 1;
            }else{
                mymap[num] += 1;
            }
        }
        
        for(map<int, int>::iterator it=mymap.begin(); it!=mymap.end(); it++){
            if(it->second==1) return it->first;
        }
        
        return -1;
    }
};

//using set
//Runtime: 32 ms, faster than 10.91% of C++ online submissions for Single Number.
//Memory Usage: 11.8 MB, less than 5.09% of C++ online submissions for Single Number.
/**
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        set<int> myset;
        
        for(int num : nums){
            if(myset.find(num)==myset.end()){
                myset.insert(num);
            }else{
                myset.erase(num);
            }
        }
        
        if(!myset.empty()){
            return *myset.begin();
        }
        
        return -1;
    }
};
**/


//math
//2∗(a+b+c)−(a+a+b+b+c)=c
/**
Complexity Analysis

Time complexity : O(n + n) = O(n). sum will call next to iterate through nums. 
We can see it as sum(list(i, for i in nums)) which means the time complexity is O(n) 
because of the number of elements(n) in nums.

Space complexity : O(n + n) = O(n). set needs space for the elements in nums **/

//Runtime: 36 ms, faster than 7.05% of C++ online submissions for Single Number.
//Memory Usage: 11.8 MB, less than 5.09% of C++ online submissions for Single Number.

/**
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        set<int> myset (nums.begin(), nums.end());
        int ans = 0;
        
        for(int e : myset){
            ans += e*2;
        }
        
        for(int e : nums){
            ans -= e;
        }
        
        return ans;
    }
};
**/

/**
Approach 4: Bit Manipulation
Concept

If we take XOR of zero and some bit, it will return that bit
a⊕0=a
If we take XOR of two same bits, it will return 0
a⊕a=0
a⊕b⊕a=(a⊕a)⊕b=0⊕b=b
So we can XOR all bits together to find the unique number.
**/

/**
Complexity Analysis

Time complexity : O(n). 
We only iterate through nums, 
so the time complexity is the number of elements in nums.

Space complexity : O(1).
**/

//Runtime: 16 ms, faster than 96.66% of C++ online submissions for Single Number.
//Memory Usage: 9.6 MB, less than 92.26% of C++ online submissions for Single Number.

/**
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans=0;
        
        for(int num : nums){
            ans^=num;
        }
        
        return ans;
    }
};
**/
