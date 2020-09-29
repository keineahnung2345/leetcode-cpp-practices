//Runtime: 276 ms, faster than 82.02% of C++ online submissions for Maximum Profit of Operating a Centennial Wheel.
//Memory Usage: 81.7 MB, less than 13.45% of C++ online submissions for Maximum Profit of Operating a Centennial Wheel.
class Solution {
public:
    int minOperationsMaxProfit(vector<int>& customers, int boardingCost, int runningCost) {
        int max_time, max_profit = INT_MIN;
        int cur = 0;
        int remain = 0;
        int n = customers.size();
        
        int time = 1;
        
        for(time = 1; time <= n; ++time){
            int board = min(4, remain+customers[time-1]);
            cur += board * boardingCost - runningCost;
            
            if(cur > max_profit){
                max_profit = cur;
                max_time = time;
            }
            
            remain += (customers[time-1] - board);
        }
        
        for(; remain; ++time){
            int board = min(4, remain);
            cur += board * boardingCost - runningCost;
            
            if(cur > max_profit){
                max_profit = cur;
                max_time = time;
            }
            
            remain -= board;
        }
        
        return (max_profit < 0) ? -1 : max_time;
    }
};
