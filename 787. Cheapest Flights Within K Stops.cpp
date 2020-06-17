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

//Single-Source Shortest Path：Dijkstra's Algorithm, priority queue
//https://leetcode.com/problems/cheapest-flights-within-k-stops/discuss/115541/JavaPython-Priority-Queue-Solution
//Runtime: 96 ms, faster than 45.17% of C++ online submissions for Cheapest Flights Within K Stops.
//Memory Usage: 17.2 MB, less than 22.17% of C++ online submissions for Cheapest Flights Within K Stops.
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        vector<vector<pair<int, int>>> edges(n);
        for(vector<int>& flight : flights){
            //src -> (dst1, price1), (dst2, price2), ...
            edges[flight[0]].emplace_back(flight[1], flight[2]);
        }
        
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        vector<int> cur;
        int curCost, curSrc, curK;
        
        //(cost from source, current node, max distance to destination allowed)
        pq.push({0, src, K+1});
        
        //visit nodes in increasing price order
        while(!pq.empty()){
            cur = pq.top(); pq.pop();
            curCost = cur[0]; curSrc = cur[1]; curK = cur[2];
            if(curSrc == dst){
                return curCost;
            }
            if(curK > 0){
                for(pair<int, int>& nei : edges[curSrc]){
                    pq.push({curCost+nei.second, nei.first, curK-1});
                }
            }
        }
        
        return -1;
    }
};
