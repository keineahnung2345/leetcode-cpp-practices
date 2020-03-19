//Runtime: 4 ms, faster than 73.48% of C++ online submissions for Minimum Cost For Tickets.
//Memory Usage: 7.8 MB, less than 100.00% of C++ online submissions for Minimum Cost For Tickets.
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int N = days.size();
        vector<int> dp(N);
        
        //1-day pass is not necessary the cheapest!
        dp[0] = min({costs[0], costs[1], costs[2]});
        
        for(int i = 1; i < N; i++){
            //the index of smallest element which is > days[i]-7: 
            //upper_bound(days.begin(), days.end(), days[i]-7)-days.begin()
            
            //interval 7
            //the index of largest element which is <= days[i]-7
            int idx7 = upper_bound(days.begin(), days.end(), days[i]-7)-days.begin()-1; 
            //interval 30
            //the index of largest element which is <= days[i]-30
            int idx30 = upper_bound(days.begin(), days.end(), days[i]-30)-days.begin()-1;
            
            // cout << "i: " << i << endl;
            // cout << "idx7: " << (idx7) << endl;
            // cout << "idx30: " << (idx30) << endl;
            
            dp[i] = min({dp[i-1] + costs[0],
                        ((idx7 >= 0 && days[i]-days[idx7]>=7)?dp[idx7]:0) + costs[1],
                        ((idx30 >= 0 && days[i]-days[idx30]>=30)?dp[idx30]:0) + costs[2]
                        });
            // cout << "dp: " << dp[i] << endl;
        }
        // cout << endl;
        
        return dp[N-1];
    }
};
