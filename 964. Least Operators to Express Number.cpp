//TLE
//1 / 159 test cases passed.
class Solution {
public:
    int x;
    int minOps;
    int target;
    vector<char> ops = {'+', '-', '*', '/'};
    
    int evaluate(string oprs){
        vector<int> opds(oprs.size()+1, x);
        
        // for(int i = 0; i < oprs.size(); ++i){
        //     cout << opds[i] << oprs[i];
        // }
        // cout << opds[oprs.size()] << endl;
        
        for(int i = 0; i < oprs.size(); ++i){
            // cout << "oprs: " << oprs.size() << ", opds: " << opds.size() << endl;
            if(oprs[i] == '*'){
                opds[i] *= opds[i+1];
                opds.erase(opds.begin()+i+1);
                oprs.erase(oprs.begin()+i);
            }else if(oprs[i] == '/'){
                opds[i] /= opds[i+1];
                opds.erase(opds.begin()+i+1);
                oprs.erase(oprs.begin()+i);
            }
        }
        
        int res = opds[0];
        
        for(int i = 0; i < oprs.size(); ++i){
            if(oprs[i] == '+'){
                res += opds[i+1];
            }else if(oprs[i] == '-'){
                res -= opds[i+1];
            }
        }
        
        // cout << "res: " << res << endl;
        return res;
    };
    
    int leastOpsExpressTarget(int x, int target) {
        minOps = INT_MAX;
        this->x = x;
        this->target = target;
        ops = {'+', '-', '*', '/'};
        
        string expr;
        queue<string> q;
        unordered_set<string> visited;
        
        q.push("");
        visited.insert("");
        
        while(!q.empty()){
            expr = q.front(); q.pop();
            
            int res = evaluate(expr);
            
            if(res == target){
                break;
            }else if(res < target){
                for(char op : {'+', '*'}){
                    if(visited.find(expr+op) == visited.end()){
                        visited.insert(expr+op);
                        q.push(expr+op);
                    }
                }
            }else{
                for(char op : {'-', '/'}){
                    if(visited.find(expr+op) == visited.end()){
                        visited.insert(expr+op);
                        q.push(expr+op);
                    }
                }
            }
        }
        
        return expr.size();
    }
};

//recursion, greedy
//https://leetcode.com/problems/least-operators-to-express-number/discuss/208445/c%2B%2B-recursive-easy-to-understand
//Runtime: 44 ms, faster than 33.96% of C++ online submissions for Least Operators to Express Number.
//Memory Usage: 6 MB, less than 83.96% of C++ online submissions for Least Operators to Express Number.
class Solution {
public:
    int leastOpsExpressTarget(int x, int target) {
        if(x == target){
            return 0;
        }else if(x > target){
            /*
            if x = 3 and target = 2,
            (1) by adding:      3/3+3/3=2, need "target" '/' and "target-1" '+'
            (2) by subtracting: 3-3/3=2, need "target-x" '-' and '/'
            */
            return min(2*target-1, 2*(x-target));
        }else{
            //x < target
            long long cur = x;
            int count = 0;
            
            //greedy, use '*' as many as possible
            while(cur < target){
                cur *= x;
                ++count;
            }
            
            if(cur == target){
                return count;
            }
            
            //cur > target
            int sub_count = INT_MAX, add_count = INT_MAX;
            
            /*
            x = 3, target = 5, cur = 9
            9-5=4, 4 is the new target
            */
            if(cur - target < target){ //?
                sub_count = count + leastOpsExpressTarget(x, cur-target);
            }
            
            /*
            x = 3, target = 5, cur = 9
            5-9/3=2, 2 is the new target
            we fall back to cur/x, so count-1
            */
            add_count = count - 1 + leastOpsExpressTarget(x, target-cur/x);
            
            //+1: current expression need to be concatenated(+/-) with the previous one
            return min(sub_count, add_count) + 1;
        }
    }
};
