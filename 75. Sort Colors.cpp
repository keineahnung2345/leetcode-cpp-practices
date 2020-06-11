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

//two pointer, dutch partitioning problem
//https://leetcode.com/problems/sort-colors/discuss/26679/C%2B%2B-one-pass-concise-solution.
//https://leetcode.com/problems/sort-colors/discuss/26481/Python-O(n)-1-pass-in-place-solution-with-explanation
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int left = 0, cur = 0, right = nums.size()-1;
        /*
        left: right boundary of 0(exclusive), serves as the next position to place 0
        right: left boundary of 2(exclusive), serves as the next position to place 2
        cur: the right boundary of 1(inclusive)
        */
        while (cur <= right) {
            // cout << left << " " << cur << " " << right << endl;
            if (nums[cur] == 0){
                /*
                put the number 0 to the position "left"
                nums[left] will be put in nums[cur], it will be visited later
                */
                swap(nums[cur++], nums[left++]);
            }else if (nums[cur] == 2){
                /*
                put the number 0 to the position "right"
                nums[right] will be put in nums[cur], it will be visited later
                (look at the condition cur <= right)
                */
                swap(nums[cur], nums[right--]);
            }else{
                /*
                the number "1" is in right position,
                so just move forward
                */
                cur++;
            }
            
            // for(int& num : nums){
            //     cout << num << " ";
            // }
            // cout << endl;
        }
    }
};
