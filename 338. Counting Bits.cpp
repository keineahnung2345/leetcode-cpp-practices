/**
Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and return them as an array.

Example 1:

Input: 2
Output: [0,1,1]
Example 2:

Input: 5
Output: [0,1,1,2,1,2]
Follow up:

It is very easy to come up with a solution with run time O(n*sizeof(integer)). But can you do it in linear time O(n) /possibly in a single pass?
Space complexity should be O(n).
Can you do it like a boss? Do it without using any builtin function like __builtin_popcount in c++ or in any other language.
**/

//Your runtime beats 60.09 % of cpp submissions.
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> ans;
        for(int i=0;i<=num;i++){
            int count = 0;
            int j = i;
            while(j!=0){
                count+=j%2;
                j/=2;
            }
            ans.push_back(count);
        }
        return ans;
    }
};

//Your runtime beats 43.45 % of cpp submissions.
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> ans;
        for(int i=0;i<=num;i++){
            ans.push_back(__builtin_popcount(i));
        }
        return ans;
    }
};

//from hint, suboptimal
//Runtime: 8 ms, faster than 99.05% of C++ online submissions for Counting Bits.
//Memory Usage: 7.8 MB, less than 100.00% of C++ online submissions for Counting Bits.
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> ans(num+1, 0);
        
        for(int i = 1; i < num+1; i++){
            ans[i] = ans[i/2] + i%2;
        }
        
        return ans;
    }
};

//Your runtime beats 97.98 % of cpp submissions.
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> ret(num+1, 0);
        for (int i = 1; i <= num; ++i)
            ret[i] = ret[i&(i-1)] + 1; //by @fengcc
            // ret[i] = ret[i/2] + i % 2; //by @sijiec
        return ret;
    }
};

/**
by @fengcc
i&(i-1) drops the lowest set bit. For example: i = 14, its binary representation is 1110, so i-1 is 1101, i&(i-1) = 1100, the number of "1" in its binary representation decrease one, so ret[i] = ret[i&(i-1)] + 1.
**/

