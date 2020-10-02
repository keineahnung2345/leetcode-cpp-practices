//Runtime: 12 ms, faster than 46.22% of C++ online submissions for Remove Duplicates from Sorted Array II.
//Memory Usage: 11.3 MB, less than 13.64% of C++ online submissions for Remove Duplicates from Sorted Array II.
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        int slow = 0, fast = 0;
        bool first;
        
        while(fast < n){
            // cout << slow << " <- " << fast << endl;
            nums[slow] = nums[fast];
            if(slow == 0 || nums[slow] != nums[slow-1]){
                first = true;
            }else{
                first = false;
            }
            
            if(first){
                ++fast;
            }else{
                while(fast < n && nums[fast] == nums[slow]){
                    ++fast;
                }
            }
            
            ++slow;
        }
        
        return slow;
    }
};

//https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/discuss/27976/3-6-easy-lines-C%2B%2B-Java-Python-Ruby
//Runtime: 4 ms, faster than 99.33% of C++ online submissions for Remove Duplicates from Sorted Array II.
//Memory Usage: 11.3 MB, less than 14.37% of C++ online submissions for Remove Duplicates from Sorted Array II.
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        int slow = 0;
        int k = 2;
        
        for(int fast = 0; fast < n; ++fast){
            if(slow < k || nums[fast] != nums[slow-k]){
                /*
                only update nums[slow] when 
                there are < k nums[fast] in the new array
                */
                nums[slow++] = nums[fast];
            }
        }
        
        return slow;
    }
};
