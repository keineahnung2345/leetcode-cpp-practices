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
