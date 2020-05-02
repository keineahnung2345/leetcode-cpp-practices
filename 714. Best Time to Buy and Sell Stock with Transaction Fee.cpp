//TLE
//20 / 44 test cases passed.
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int N = prices.size();
        vector<int> profits(N, 0);
        int last = -1;
        
        for(int i = 0; i < N; i++){
            int notUseBefore = prices[i] - fee - 
                *min_element(prices.begin(), prices.begin()+i);
            int noOp = (i > 0) ? profits[i-1] : 0;
            
            // int useBefore =  prices[i] - fee - 
                // *min_element(prices.begin()+last+1, prices.begin()+i) + 
                // ((last > 0) ? profits[last] : 0);
            int useBefore = 0;
            for(int last = 0; last < i; last++){
                 useBefore = max(useBefore, 
                    prices[i] - fee - 
                    *min_element(prices.begin()+last+1, prices.begin()+i) +
                    ((last > 0) ? profits[last] : 0)
                    );
            }
            
            if(max(notUseBefore, useBefore) > noOp){
                last = i;
            }
            profits[i] = max({notUseBefore, useBefore, noOp});
            
            // cout << profits[i] << endl;
        }
        
        return profits[N-1];
    }
};

//DP
//Runtime: 236 ms, faster than 10.33% of C++ online submissions for Best Time to Buy and Sell Stock with Transaction Fee.
//Memory Usage: 60.1 MB, less than 5.88% of C++ online submissions for Best Time to Buy and Sell Stock with Transaction Fee.
//time: O(N), space: O(N)
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<int> hold(n+1, INT_MIN), empty(n+1, 0);
        
        for(int i = 1; i <= n; i++){
            //no op or buy
            hold[i] = max(hold[i-1], empty[i-1]-prices[i-1]-fee);
            //no op or sell
            empty[i] = max(empty[i-1], hold[i-1]+prices[i-1]);
            // cout << hold[i] << ", " << empty[i] << endl;
        }
        
        return max(hold[n], empty[n]);
    }
};

//DP with O(1) space
//Runtime: 232 ms, faster than 11.12% of C++ online submissions for Best Time to Buy and Sell Stock with Transaction Fee.
//Memory Usage: 55.3 MB, less than 5.88% of C++ online submissions for Best Time to Buy and Sell Stock with Transaction Fee.
//time: O(N), space: O(1)
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        int hold = INT_MIN, empty = 0;
        int newhold;
        
        for(int i = 1; i <= n; i++){
            //no op or buy
            newhold = max(hold, empty-prices[i-1]-fee);
            //no op or sell
            empty = max(empty, hold+prices[i-1]);
            // cout << hold[i] << ", " << empty[i] << endl;
            hold = newhold;
        }
        
        return max(hold, empty);
    }
};

//Approach #1: Dynamic Programming with O(1) space
//Runtime: 148 ms, faster than 32.31% of C++ online submissions for Best Time to Buy and Sell Stock with Transaction Fee.
//Memory Usage: 13 MB, less than 100.00% of C++ online submissions for Best Time to Buy and Sell Stock with Transaction Fee.
//time: O(N), space: O(1)
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int cash = 0, hold = -prices[0];
        for(int i = 1; i < prices.size(); i++){
            /*
            cash[i] = cash[i-1]: do nothing
            cash[i] = hold+prices[i]-fee: sell the stock held in last day
            */
            cash = max(cash, hold + prices[i] - fee);
            /*
            hold[i] = hold[i-1]: do nothing
            hold = cash[i-1] - prices[i]: buy stock today
            */
            hold = max(hold, cash - prices[i]);
        }
        return cash;
    }
};
