//line sweep
//Runtime: 556 ms, faster than 28.20% of C++ online submissions for Corporate Flight Bookings.
//Memory Usage: 67.8 MB, less than 83.30% of C++ online submissions for Corporate Flight Bookings.
//time: O(N+bookings), space: O(N)
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> counter(n);
        
        for(vector<int>& book : bookings){
            int i = book[0]-1, j = book[1]-1;
            counter[i] += book[2];
            if(j+1 < n) counter[j+1] -= book[2];
        }
        
        for(int i = 1; i < n; ++i){
            counter[i] += counter[i-1];
        }
        
        return counter;
    }
};
