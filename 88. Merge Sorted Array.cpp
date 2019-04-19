//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Merge Sorted Array.
//Memory Usage: 8.6 MB, less than 100.00% of C++ online submissions for Merge Sorted Array.

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int cur1 = 0, cur2 = 0;
        nums1.resize(m);
        nums2.resize(n);
        while(cur2 < n){
            if(m == 0 || nums1.back() <= nums2[cur2]){
                //nums1 has been fully processed
                nums1.push_back(nums2[cur2]);
                //have processed a node in nums2
                cur2++;
            }else if(nums2[cur2] <= nums1[cur1]){
                nums1.insert(nums1.begin()+cur1, nums2[cur2]);
                //have processed a node in nums2
                cur2++;
            }
            //every time we look at one node in nums1
            cur1++;
        }
        nums1.resize(m+n);
    }
};

//https://leetcode.com/problems/merge-sorted-array/discuss/29522/This-is-my-AC-code-may-help-you
//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Merge Sorted Array.
//Memory Usage: 8.7 MB, less than 100.00% of C++ online submissions for Merge Sorted Array.

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m-1, j = n-1, k = m+n-1;
        while(i >= 0 && j >= 0){
            if(nums1[i] > nums2[j]){
                nums1[k--] = nums1[i--];
            }else{
                nums1[k--] = nums2[j--];
            }
        }
        
        while(j >= 0){
            nums1[k--] = nums2[j--];
        }
    }
};
