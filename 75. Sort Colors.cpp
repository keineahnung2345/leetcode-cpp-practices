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
