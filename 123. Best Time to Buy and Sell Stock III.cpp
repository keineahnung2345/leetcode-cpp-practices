//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/discuss/39611/Is-it-Best-Solution-with-O(n)-O(1).
//Runtime: 8 ms, faster than 68.97% of C++ online submissions for Best Time to Buy and Sell Stock III.
//Memory Usage: 7.3 MB, less than 100.00% of C++ online submissions for Best Time to Buy and Sell Stock III.
//time: O(N), space: O(1)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //the cash in hand when we have bought 1 or 2 stocks
        /*
        we need to initialize hold1 and hold2 to INT_MIN, 
        because they are required to compared with "-price"
        */
        int hold1 = INT_MIN, hold2 = INT_MIN;
        //the cash in hand when we have sold 1 or 2 stocks
        /*
        the minimum of release1 and release2 is 0, 
        no need to be INT_MIN
        */
        int release1 = 0, release2 = 0;
        
        for(int price : prices){
            //their values depend on the value in previous iteration, so their order is required to be like this
            //release2 is always >= release1
            release2 = max(release2, hold2+price);
            //hold2 is always >= hold1
            hold2 = max(hold2, release1-price);
            //release1 is always >= 0
            release1 = max(release1, price+hold1);
            hold1 = max(hold1, -price);
        }
        
        //release2 is always max(release1, release2)
        return release2;
    }
};
