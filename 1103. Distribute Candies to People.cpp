//Runtime: 4 ms, faster than 65.76% of C++ online submissions for Distribute Candies to People.
//Memory Usage: 8.6 MB, less than 100.00% of C++ online submissions for Distribute Candies to People.

class Solution {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        vector<int> ans(num_people);
        
        for(int i = 1; candies > 0; i++){
            ans[(i-1) % num_people] += min(candies, i);
            candies = max(0, candies - i);
        }
        
        return ans;
    }
};
