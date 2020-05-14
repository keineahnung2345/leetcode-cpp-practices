/**
On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).

Once you pay the cost, you can either climb one or two steps. You need to find minimum cost to reach the top of the floor, and you can either start from the step with index 0, or the step with index 1.

Example 1:
Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.
Example 2:
Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].
Note:
cost will have a length in the range [2, 1000].
Every cost[i] will be an integer in the range [0, 999].
**/

//TLE
class Solution {
public:
    int rMinCost(vector<int>& cost, int start){
        if(start >= cost.size()){
            return 0;
        }
        int curCost = cost[start];
        // cout << curCost << endl;
        return curCost + min(rMinCost(cost, start+1), rMinCost(cost, start+2));
    }
    
    int minCostClimbingStairs(vector<int>& cost) {
        return min(rMinCost(cost, 0), rMinCost(cost, 1));
    }
};

//Runtime: 12 ms, faster than 62.24% of C++ online submissions for Min Cost Climbing Stairs.
//Memory Usage: 8.8 MB, less than 98.94% of C++ online submissions for Min Cost Climbing Stairs.

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> costSum = vector<int>(cost.size()+2, 0);
        
        for(int i = cost.size()-1; i >=0; i--){
            costSum[i] = cost[i] + min(costSum[i+1], costSum[i+2]);
        }
        
        /*
        the problem states: "reach the top of the floor",
        it means reaching the -1th floor,
        and we can go to -1th floor from either 0th or 1st floor,
        so here we use min(costSum[0], costSum[1])
        */
        return min(costSum[0], costSum[1]);
    }
};

/**
Approach #1: Dynamic Programming [Accepted]
Intuition

There is a clear recursion available: the final cost f[i] to climb the staircase from some step i is f[i] = cost[i] + min(f[i+1], f[i+2]). This motivates dynamic programming.

Algorithm

Let's evaluate f backwards in order. That way, when we are deciding what f[i] will be, we've already figured out f[i+1] and f[i+2].

We can do even better than that. At the i-th step, let f1, f2 be the old value of f[i+1], f[i+2], and update them to be the new values f[i], f[i+1]. We keep these updated as we iterate through i backwards. At the end, we want min(f1, f2).
**/

/**
Complexity Analysis
Time Complexity: O(N) where N is the length of cost.
Space Complexity: O(1), the space used by f1, f2.
**/

//Runtime: 8 ms, faster than 99.66% of C++ online submissions for Min Cost Climbing Stairs.
//Memory Usage: 8.6 MB, less than 100.00% of C++ online submissions for Min Cost Climbing Stairs.
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int f1 = 0, f2 = 0;
        for(int i = cost.size()-1; i >= 0; i--){
            int f0 = cost[i] + min(f1, f2);
            f2 = f1;
            f1 = f0;
        }
        return min(f1, f2);
    }
};
