/**
Given two arrays, write a function to compute their intersection.

Example 1:

Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]
Example 2:

Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]
Note:

Each element in the result should appear as many times as it shows in both arrays.
The result can be in any order.
Follow up:

What if the given array is already sorted? How would you optimize your algorithm?
What if nums1's size is small compared to nums2's size? Which algorithm is better?
What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?
**/

//Runtime: 8 ms, faster than 100.00% of C++ online submissions for Intersection of Two Arrays II.
//Memory Usage: 8.9 MB, less than 95.22% of C++ online submissions for Intersection of Two Arrays II.

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        
        vector<int> ans;
        
        int cur1 = 0, cur2 = 0;
        
        while(cur1 < nums1.size() && cur2 < nums2.size()){
            if(nums1[cur1] == nums2[cur2]){
                ans.push_back(nums1[cur1]);
                cur1++;
                cur2++;
            }else if(nums1[cur1] < nums2[cur2]){
                cur1++;
            }else{
                cur2++;
            }
        }
        
        return ans;
    }
};
