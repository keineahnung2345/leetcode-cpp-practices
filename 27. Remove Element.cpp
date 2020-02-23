//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Remove Element.
//Memory Usage: 8.6 MB, less than 67.65% of C++ online submissions for Remove Element.

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int l = nums.size();
        nums.erase(remove(nums.begin(), nums.end(), val), nums.end());
        // cout << l << "-> " << nums.size() << endl;
        return nums.size();
    }
};
