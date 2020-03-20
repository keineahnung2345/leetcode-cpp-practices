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
