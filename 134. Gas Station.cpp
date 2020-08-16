//Runtime: 168 ms, faster than 18.77% of C++ online submissions for Gas Station.
//Memory Usage: 10 MB, less than 27.31% of C++ online submissions for Gas Station.
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        
        //candidate start point
        vector<int> cand;
        
        for(int i = 0; i < n; ++i){
            if(gas[i] >= cost[i])
                cand.push_back(i);
        }
        
        for(int start : cand){
            bool canreach = true;
            int cur = 0;
            for(int i = start; i < start+n; ++i){
                cur += gas[i%n] - cost[i%n];
                if(cur < 0){
                    canreach = false;
                    break;
                }
            }
            if(canreach){
                return start;
            }
        }
        
        return -1;
    }
};
