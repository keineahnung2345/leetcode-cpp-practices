//backtrack
//Runtime: 4 ms, faster than 89.87% of C++ online submissions for Generate Parentheses.
//Memory Usage: 7 MB, less than 100.00% of C++ online submissions for Generate Parentheses.
class Solution {
public:
    vector<char> pars =  {'(', ')'};
    
    void backtrack(int& n, string& comb, vector<string>& combs){
        int open = count(comb.begin(), comb.end(), '(');
        int close = comb.size() - open;
        
        //short for open == n && close == n
        if(close == n){
            combs.push_back(comb);
        }
        
        for(int i = 0; i < pars.size(); i++){
            //only when open par's count < n, we can append open par
            //only when close par's count < open par's count, we can append close par
            if((i == 0 && open < n) || (i == 1 && open > close)){
                comb += pars[i];
                backtrack(n, comb, combs);
                comb.pop_back();
            }
        }
    };
    
    vector<string> generateParenthesis(int n) {
        string comb;
        vector<string> combs;
        backtrack(n, comb, combs);
        return combs;
    }
};
