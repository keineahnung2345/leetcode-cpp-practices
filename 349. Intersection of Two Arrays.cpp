/**
Given two arrays, write a function to compute their intersection.

Example 1:

Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]
Example 2:

Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [9,4]
Note:

Each element in the result must be unique.
The result can be in any order.
**/

//Runtime: 16 ms, faster than 14.90% of C++ online submissions for Intersection of Two Arrays.
//Memory Usage: 8.8 MB, less than 99.41% of C++ online submissions for Intersection of Two Arrays.

/**
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        for(int num : nums1){
            if(find(nums2.begin(), nums2.end(), num)!=nums2.end()){
                if(find(ans.begin(), ans.end(), num)==ans.end()){
                    ans.push_back(num);
                }
            }
        }
        return ans;
    }
};
**/

//Runtime: 12 ms, faster than 58.27% of C++ online submissions for Intersection of Two Arrays.
//Memory Usage: 9.8 MB, less than 11.28% of C++ online submissions for Intersection of Two Arrays.
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        set<int> s1(nums1.begin(), nums1.end());
        set<int> s2(nums2.begin(), nums2.end());
        vector<int> ans(max(nums1.size(), nums2.size()));
        vector<int>::iterator it = set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), ans.begin());
        ans.resize(it - ans.begin());
        return ans;
    }
};
