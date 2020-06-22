//Runtime: 40 ms, faster than 7.36% of C++ online submissions for Single Number III.
//Memory Usage: 12.3 MB, less than 5.00% of C++ online submissions for Single Number III.
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        set<int> fset;
        set<int> sset;
        set<int> rset;
        for(int num : nums){
            if(fset.find(num)==fset.end()){
                fset.insert(num);
            }else{
                sset.insert(num);
            }
        }
        vector<int> ans(fset.size());
        auto v_it = set_difference(fset.begin(), fset.end(), sset.begin(), sset.end(), ans.begin());
        ans.resize(v_it-ans.begin());
        return ans;
    }
};

//bit manipulation
//https://leetcode.com/problems/single-number-iii/discuss/68900/Accepted-C%2B%2BJava-O(n)-time-O(1)-space-Easy-Solution-with-Detail-Explanations
//Runtime: 20 ms, faster than 59.77% of C++ online submissions for Single Number III.
//Memory Usage: 10.1 MB, less than 54.17% of C++ online submissions for Single Number III.
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        //xor all the numbers
        int diff = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
        //get least significant bit
        diff &= ~(diff-1);
        //another way
        //diff &= -diff;
        
        vector<int> ans(2, 0);
        
        for(int& num : nums){
            if(num & diff){
                //group 1: set at "diff"'s bit
                ans[0] ^= num;
            }else{
                //group 2: not set at "diff"'s bit
                ans[1] ^= num;
            }
        }
        
        return ans;
    }
};
