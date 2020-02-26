//https://leetcode.com/problems/two-city-scheduling/discuss/278716/C%2B%2B-O(n-log-n)-sort-by-savings
//time: O(nlogn), space: O(1)
//Runtime: 4 ms, faster than 89.86% of C++ online submissions for Two City Scheduling.
//Memory Usage: 9.3 MB, less than 94.74% of C++ online submissions for Two City Scheduling.

class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        //costs.size() is always even
        int N = costs.size()/2;
        int ans = 0;
        //the first N element will be the elements whose 
        //A_cost - B_cost is smaller,
        //they should fly to A
        sort(costs.begin(), costs.end(),
             [](vector<int> &v1, vector<int> &v2) {
                 return v1[0] - v1[1] < v2[0] - v2[1];
             });
        for(int i = 0; i < N; i++){
            ans += costs[i][0] + costs[i+N][1];
        }
        return ans;
    }
};

//optimized
//Runtime: 4 ms, faster than 89.86% of C++ online submissions for Two City Scheduling.
//Memory Usage: 9.3 MB, less than 94.74% of C++ online submissions for Two City Scheduling.

class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        //costs.size() is always even
        int N = costs.size()/2;
        int ans = 0;
        //the first N element will be the elements whose 
        //A_cost - B_cost is smaller,
        //they should fly to A
        nth_element(costs.begin(), costs.begin() + N, 
            costs.end(), [](vector<int>& v1, vector<int>& v2){
                return v1[0] - v1[1] < v2[0] - v2[1];
            });
        for(int i = 0; i < N; i++){
            ans += costs[i][0] + costs[i+N][1];
        }
        return ans;
    }
};
