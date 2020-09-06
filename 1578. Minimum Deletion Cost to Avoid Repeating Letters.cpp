//Runtime: 360 ms, faster than 33.33% of C++ online submissions for Minimum Deletion Cost to Avoid Repeating Letters.
//Memory Usage: 95.7 MB, less than 33.33% of C++ online submissions for Minimum Deletion Cost to Avoid Repeating Letters.
class Solution {
public:
    int minCost(string s, vector<int>& cost) {
        int n = s.size();
        int ans = 0;
        
        for(int i = 0; i < n; ){
            int maintain_cost = cost[i];
            int j;
            for(j = i+1; j < n && s[j] == s[i]; ++j){
                maintain_cost = max(maintain_cost, cost[j]);
            }
            
            if(j-i > 1){
                ans += accumulate(cost.begin()+i, cost.begin()+j, 0) - maintain_cost;
            }
            
            i = j;
        }
        
        return ans;
    }
};

//cleaner
//https://leetcode.com/problems/minimum-deletion-cost-to-avoid-repeating-letters/discuss/831588/JavaC%2B%2BPython-Straight-Forward
//Runtime: 388 ms, faster than 33.33% of C++ online submissions for Minimum Deletion Cost to Avoid Repeating Letters.
//Memory Usage: 95.5 MB, less than 33.33% of C++ online submissions for Minimum Deletion Cost to Avoid Repeating Letters.
class Solution {
public:
    int minCost(string s, vector<int>& cost) {
        int n = s.size();
        int max_cost = 0, sum_cost = 0;
        int res = 0;
        
        for(int i = 0; i < n; ++i){
            if(i-1 >= 0 && s[i] != s[i-1]){
                //end the old session and start a new one
                res += sum_cost - max_cost;
                sum_cost = max_cost = 0;
            }
            //in a session, update sum_cst and max_cost
            sum_cost += cost[i];
            max_cost = max(max_cost, cost[i]);
        }
        
        res += sum_cost - max_cost;
        
        return res;
    }
};
