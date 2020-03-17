//counting sort
//Runtime: 4 ms, faster than 69.48% of C++ online submissions for Sort Colors.
//Memory Usage: 7.8 MB, less than 100.00% of C++ online submissions for Sort Colors.
class Solution {
public:
    void sortColors(vector<int>& nums) {
        map<int, int> counter;
        for(int& num : nums){
            counter[num]++;
        }
        
        int cur = 0;
        for(auto it = counter.begin(); it != counter.end(); it++){
            while(it->second){
                nums[cur++] = it->first;
                it->second--;
            }
        }
    }
};

//two pointer
//https://leetcode.com/problems/sort-colors/discuss/26679/C%2B%2B-one-pass-concise-solution.
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int left = 0, cur = 0, right = nums.size()-1;
        while (cur <= right) {
            // cout << left << " " << cur << " " << right << endl;
            if (nums[cur] == 0){
                swap(nums[cur++], nums[left++]);
            }else if (nums[cur] == 2){
                swap(nums[cur], nums[right--]);
            }else{
                cur++;
            }
            
            // for(int& num : nums){
            //     cout << num << " ";
            // }
            // cout << endl;
        }
    }
};
