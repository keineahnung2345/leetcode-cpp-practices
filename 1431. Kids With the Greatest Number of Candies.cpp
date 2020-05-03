//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Kids With the Greatest Number of Candies.
//Memory Usage: 9.2 MB, less than 100.00% of C++ online submissions for Kids With the Greatest Number of Candies.
class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int maxCandy = *max_element(candies.begin(), candies.end());
        int n = candies.size();
        
        vector<bool> ans(n);
        
        for(int i = 0; i < n; i++){
            ans[i] = (maxCandy - candies[i] <= extraCandies);
        }
        
        return ans;
    }
};
