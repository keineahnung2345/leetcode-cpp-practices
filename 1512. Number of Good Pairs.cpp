//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Number of Good Pairs.
//Memory Usage: 7.2 MB, less than 100.00% of C++ online submissions for Number of Good Pairs.
class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        map<int, int> counter;
        
        for(int num : nums){
            counter[num]++;
        }
        
        int ans = 0;
        
        for(auto it = counter.begin(); it != counter.end(); ++it){
            if(it->second > 1){
                ans += it->second * (it->second-1) /2;
            }
        }
        
        return ans;
    }
};
