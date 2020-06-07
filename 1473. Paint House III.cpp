//TLE
//24 / 59 test cases passed.
class Solution {
public:
    int ans;
    
    void backtrack(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target, int start, int curCost){
        // cout << "start: " << start << ", curCost: " << curCost << ", target: " << target << endl;
        // cout << "houses: ";
        // for(int i = 0; i < houses.size(); i++){
        //     cout << houses[i] << " ";
        // }
        // cout << endl;
        
        if(start == m){
            //reach end of houses
            //no more neighborhoods to add
            if(target == 0){
                ans = min(ans, curCost);
                // cout << "ans: " << ans << endl;
            }
        }else if(houses[start] != 0){
            //current house is already painted
            int newtarget = target;
            if(start == 0){
                // cout << "start is 0" << endl;
                newtarget = target-1;
            }else if(start > 0 && houses[start-1] != 0 && houses[start] != houses[start-1]){
                // cout << "color not equal to last" << endl;
                newtarget = target-1;
            }
            if(newtarget < 0) return;
            backtrack(houses, cost, m, n, newtarget, start+1, curCost);
        }else{
            for(int i = 0; i < n; i++){
                int newtarget = target;
                if(start == 0){
                    // cout << "start is 0" << endl;
                    newtarget = target-1;
                }else if(start > 0 && houses[start-1] != 0 && i+1 != houses[start-1]){
                    // cout << "color not equal to last" << endl;
                    newtarget = target-1;
                }
                if(newtarget < 0) continue;
                houses[start] = i+1;
                // cout << "target: " << target << " -> " << newtarget << endl;
                backtrack(houses, cost, m, n, newtarget, start+1, curCost+cost[start][i]);
                houses[start] = 0;
            }
        }
    };
    
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        ans = INT_MAX;
        backtrack(houses, cost, m, n, target, 0, 0);
        return (ans == INT_MAX) ? -1 : ans;
    }
};
