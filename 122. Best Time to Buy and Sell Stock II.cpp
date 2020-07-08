/**
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times).

Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).

Example 1:

Input: [7,1,5,3,6,4]
Output: 7
Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
             Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
Example 2:

Input: [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
             Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
             engaging multiple transactions at the same time. You must sell before buying again.
Example 3:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
**/

//Runtime: 8 ms, faster than 99.42% of C++ online submissions for Best Time to Buy and Sell Stock II.
//Memory Usage: 9.3 MB, less than 97.55% of C++ online submissions for Best Time to Buy and Sell Stock II.
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() == 0) return 0;
        
        int ans = 0;
        int start = prices[0], end = prices[0];
        
        for(int i = 0; i < prices.size(); i++){
            if(prices[i] > end){
                //still in the old session
                //update old end
                end = prices[i];
            }else{
                //sell
                ans += (end - start);
                //restart a session
                start = prices[i];
                end = prices[i];
            }
        }
        
        if(end > start) ans += (end - start);
        
        return ans;
    }
};


/**
Solution
Approach 1: Brute Force
In this case, we simply calculate the profit corresponding to all the possible sets of transactions and find out the maximum profit out of them.
**/

/**
//Java
class Solution {
    public int maxProfit(int[] prices) {
        return calculate(prices, 0);
    }

    public int calculate(int prices[], int s) {
        if (s >= prices.length)
            return 0;
        int max = 0;
        for (int start = s; start < prices.length; start++) {
            int maxprofit = 0;
            for (int i = start + 1; i < prices.length; i++) {
                if (prices[start] < prices[i]) {
                    int profit = calculate(prices, i + 1) + prices[i] - prices[start];
                    if (profit > maxprofit)
                        maxprofit = profit;
                }
            }
            if (maxprofit > max)
                max = maxprofit;
        }
        return max;
    }
}
**/

/**
Complexity Analysis

Time complexity : O(n^n). Recursive function is called n^n times.

Space complexity : O(n). Depth of recursion is nn. 
**/

/**
Approach 2: Peak Valley Approach
Algorithm

Say the given array is:

[7, 1, 5, 3, 6, 4].

If we plot the numbers of the given array on a graph, we get:
**/

/**
If we analyze the graph, we notice that the points of interest are the consecutive valleys and peaks.

Mathematically speaking: Total Profit= \sum_{i}(height(peak_i)-height(valley_i)) TotalProfit=∑ i(height(peak i)−height(valley i))

The key point is we need to consider every peak immediately following a valley to maximize the profit. In case we skip one of the peaks (trying to obtain more profit), we will end up losing the profit over one of the transactions leading to an overall lesser profit.

For example, in the above case, if we skip peak_ipeak i and valley_jvalley j trying to obtain more profit by considering points with more difference in heights, the net profit obtained will always be lesser than the one obtained by including them, since CC will always be lesser than A+BA+B.
**/

/**
Complexity Analysis
Time complexity : O(n). Single pass.
Space complexity : O(1). Constant space required. 
**/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() == 0) return 0;
        int ans = 0;
        int valley = prices[0], peak = prices[0];
        int cur = 0;
        
        while(cur < prices.size() - 1){
            //find valley, it's smaller than its right point
            while(cur < prices.size() - 1 && prices[cur] >= prices[cur+1]){
                cur++;
            }
            valley = prices[cur];
            
            //find peak, it's larger than its right point
            while(cur < prices.size() - 1 && prices[cur] <= prices[cur+1]){
                cur++;
            }
            peak = prices[cur];
            ans += (peak - valley);
        }
        return ans;
    }
};

/**
Approach 3: Simple One Pass
Algorithm

This solution follows the logic used in Approach 2 itself, but with only a slight variation. In this case, instead of looking for every peak following a valley, we can simply go on crawling over the slope and keep on adding the profit obtained from every consecutive transaction. In the end,we will be using the peaks and valleys effectively, but we need not track the costs corresponding to the peaks and valleys along with the maximum profit, but we can directly keep on adding the difference between the consecutive numbers of the array if the second number is larger than the first one, and at the total sum we obtain will be the maximum profit. This approach will simplify the solution. This can be made clearer by taking this example:

[1, 7, 2, 3, 6, 7, 6, 7]

The graph corresponding to this array is:
**/

/**
From the above graph, we can observe that the sum A+B+CA+B+C is equal to the difference DD corresponding to the difference between the heights of the consecutive peak and valley.
**/

/**
Complexity Analysis

Time complexity : O(n)O(n). Single pass.

Space complexity: O(1)O(1). Constant space needed.
**/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() == 0) return 0;
        int ans = 0;
        for(int i = 0; i < prices.size() - 1; i++){
            ans += max(0, prices[i+1] - prices[i]);
        }
        return ans;
    }
};

//Greedy
//Runtime: 12 ms, faster than 15.03% of C++ online submissions for Best Time to Buy and Sell Stock II.
//Memory Usage: 13.4 MB, less than 6.35% of C++ online submissions for Best Time to Buy and Sell Stock II.
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int lastMin = INT_MAX;
        int ans = 0;
        
        for(int price : prices){
            if(price - lastMin > 0){
                ans += (price - lastMin);
                //lastMin is used, so update it
                lastMin = price;
            }else{
                //continue to find the minimum
                lastMin = min(lastMin, price);
            }
        }
        
        return ans;
    }
};

//monotonic deque
//Runtime: 12 ms, faster than 71.71% of C++ online submissions for Best Time to Buy and Sell Stock II.
//Memory Usage: 13.5 MB, less than 5.41% of C++ online submissions for Best Time to Buy and Sell Stock II.
//time: O(N), space: O(N)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        
        //just for trigger when the scanning ends
        prices.push_back(0);
        //increasing deque
        deque<int> deq;
        
        int profit = 0;
        
        for(int i = 0; i < n+1; ++i){
            /*
            start to process deque's content
            when we meet a smaller element
            */
            /*
            we will process all elements from deque in one pass,
            so don't need a while loop here
            */
            if(!deq.empty() && prices[i] < prices[deq.back()]){
                /*
                only when there are >= 2 choosable prices,
                we can start a transaction
                */
                if(deq.size() >= 2){
                    profit += prices[deq.back()] - prices[deq.front()];
                }
                deq.clear();
            }
            
            deq.push_back(i);
        }
        
        return profit;
    }
};

