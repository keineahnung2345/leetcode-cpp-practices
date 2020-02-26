//Runtime: 8 ms, faster than 53.23% of C++ online submissions for Distance Between Bus Stops.
//Memory Usage: 9.2 MB, less than 100.00% of C++ online submissions for Distance Between Bus Stops.

class Solution {
public:
    int distanceBetweenBusStops(vector<int>& distance, int start, int destination) {
        int total = accumulate(distance.begin(), distance.end(), 0);
        int ans = 0;
        if(start > destination){
            int tmp = start;
            start = destination;
            destination = tmp;
        }
        for(int i = start; i < destination; i++){
            ans += distance[i];
        }
        
        ans = min(ans, total - ans);
        
        return ans;
    }
};
