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

//Greedy
//Runtime: 8 ms, faster than 96.63% of C++ online submissions for Gas Station.
//Memory Usage: 10 MB, less than 35.07% of C++ online submissions for Gas Station.
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        
        int total = 0;
        
        for(int i = 0; i < n; ++i){
            total += gas[i] - cost[i];
        }
        
        if(total < 0){
            return -1;
        }
        
        /*
        If the total number of gas is bigger than 
        the total number of cost. 
        There must be a solution.
        
        Proof:
        http://blog.shengwei.li/leetcode-gas-station/
        - If there is only one gas station, it’s true.
        - If there are two gas stations a and b, and gas(a) cannot afford cost(a), i.e., gas(a) < cost(a), then gas(b) must be greater than cost(b), i.e., gas(b) > cost(b), since gas(a) + gas(b) > cost(a) + cost(b); so there must be a way too.
        - If there are three gas stations a, b, and c, where gas(a) < cost(a), i.e., we cannot travel from a to b directly, then:
        - either if gas(b) < cost(b), i.e., we cannot travel from b to c directly, then gas(c) > cost(c), so we can start at c and travel to a; since gas(b) < cost(b), gas(c) + gas(a) must be greater than cost(c) + cost(a), so we can continue traveling from a to b. **Key Point:** this can be considered as there is one station at c’ with gas(c’) = gas(c) + gas(a) and the cost from c’ to b is cost(c’) = cost(c) + cost(a), and the problem reduces to a problem with two stations. This in turn becomes the problem with two stations above.
        - or if gas(b) >= cost(b), we can travel from b to c directly. Similar to the case above, this problem can reduce to a problem with two stations b’ and a, where gas(b’) = gas(b) + gas(c) and cost(b’) = cost(b) + cost(c). Since gas(a) < cost(a), gas(b’) must be greater than cost(b’), so it’s solved too.
        - For problems with more stations, we can reduce them in a similar way. In fact, as seen above for the example of three stations, the problem of two stations can also reduce to the initial problem with one station.
        */
        
        int start = 0, tank = 0;
        for(int i = 0; i < n; ++i){
            tank += gas[i] - cost[i];
            if(tank < 0){
                /*
                if A cannot reach B, 
                then all C btw A and B cannot reach B
                (A is start, B is i) 
                so we choose new start as some position after B
                
                Proof: 
                http://blog.shengwei.li/leetcode-gas-station/
                say there is a point C between A and B -- that is A can reach C but cannot reach B. Since A cannot reach B, the gas collected between A and B is short of the cost. Starting from A, at the time when the car reaches C, it brings in gas >= 0, and the car still cannot reach B. Thus if the car just starts from C, it definitely cannot reach B.
                */
                start = i+1;
                tank = 0;
            }
        }
        
        return start;
    }
};
