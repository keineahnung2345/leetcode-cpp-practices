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

//Approach 1: Brute Force, recursion
//Runtime: 20 ms, faster than 11.14% of C++ online submissions for Generate Parentheses.
//Memory Usage: 6.9 MB, less than 100.00% of C++ online submissions for Generate Parentheses.
//time: O(2^n*n), space: O(2^n*n)
class Solution {
public:
    bool valid(string& comb){
        int balance = 0;
        for(char c : comb){
            if(c == '(') balance++;
            else balance--;
            if(balance < 0) return false;
        }
        return (balance == 0);
    }
    
    void generateAll(string& comb, vector<string>& combs, int n){
        if(comb.size() == 2*n){
            // cout << comb << endl;
            if(valid(comb))combs.push_back(comb);
            return;
        }
        
        for(char c : {'(', ')'}){
            comb.push_back(c);
            generateAll(comb, combs, n);
            comb.pop_back();
        }
    }
    
    vector<string> generateParenthesis(int n) {
        string comb;
        vector<string> combs;
        generateAll(comb, combs, n);
        return combs;
    }
};
