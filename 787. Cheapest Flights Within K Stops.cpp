//Single-Source Shortest Path：Bellman-Ford Algorithm
//Runtime: 36 ms, faster than 74.30% of C++ online submissions for Cheapest Flights Within K Stops.
//Memory Usage: 10.9 MB, less than 72.65% of C++ online submissions for Cheapest Flights Within K Stops.
//https://leetcode.com/problems/cheapest-flights-within-k-stops/discuss/115596/c%2B%2B-8-line-bellman-ford
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        /*
        n: [1, 100]
        price: [1, 10000]
        */
        int MAX = 1e6+1;
        vector<int> dist(n, MAX);
        
        //base case
        dist[src] = 0;
        for(vector<int>& flight : flights){
            //whether use flight[0] as middle point
            if(flight[0] == src)
                dist[flight[1]] = flight[2];
        }
        
        //relax for K times
        while(K-- > 0){
            // cout << "=============" << endl;
            //relax
            vector<int> tmp(dist);
            for(vector<int>& flight : flights){
                //whether use flight[0] as middle point
                /*
                tmp cannot depend on itself!
                it must be calculated from "dist"(from previous iteration!)
                */
                tmp[flight[1]] = min(tmp[flight[1]], dist[flight[0]] + flight[2]);
                // cout << flight[1] << ": " << tmp[flight[1]] << endl;
            }
            swap(tmp, dist);
        }
        // cout << endl;
        
        return dist[dst] == MAX ? -1 : dist[dst];
    }
};
