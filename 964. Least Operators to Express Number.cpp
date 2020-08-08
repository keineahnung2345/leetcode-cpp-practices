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
