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
//time: O(2^(2n)*n), space: O(2^(2n)*n)
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

//Approach 1: Brute Force, recursion
//Runtime: 16 ms, faster than 15.92% of C++ online submissions for Generate Parentheses.
//Memory Usage: 12.4 MB, less than 92.56% of C++ online submissions for Generate Parentheses.
/*
time: O(2^(2n)*n), space: O(2^(2n)*n)
we may choose either ( or ) for a comb of size 2*n,
so there are total 2^(2n) possibilities.
And for each possibility, we need to spend O(n) time to check for its validity.
*/
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        if(n == 0) return {""};
        
        vector<string> ans;
        
        for(int c = 0; c < n; c++){
            vector<string> lefts = generateParenthesis(c);
            vector<string> rights = generateParenthesis(n-1-c);
            for(string& left : lefts){
                for(string& right : rights){
                    ans.push_back("(" + left + ")" + right);
                }
            }
        }
        
        return ans;
    }
};

//backtrack
//Runtime: 4 ms, faster than 89.84% of C++ online submissions for Generate Parentheses.
//Memory Usage: 11.6 MB, less than 92.56% of C++ online submissions for Generate Parentheses.
//time: O(4^n/sqrt(n)), space: O(4^n/sqrt(n))
class Solution {
public:
    void backtrack(string& comb, vector<string>& combs, int open, int close, int n){
        if(comb.size() == n*2){
            combs.push_back(comb);
            return;
        }
        
        if(open < n){
            comb += '(';
            backtrack(comb, combs, open+1, close, n);
            comb.pop_back();
        }
        
        if(close < open){
            comb += ')';
            backtrack(comb, combs, open, close+1, n);
            comb.pop_back();
        }
    }
    
    vector<string> generateParenthesis(int n) {
        string comb = "";
        vector<string> combs;
        backtrack(comb, combs, 0, 0, n);
        return combs;
    }
};

//Approach 3: Closure Number
//Runtime: 20 ms, faster than 11.14% of C++ online submissions for Generate Parentheses.
//Memory Usage: 13.3 MB, less than 90.08% of C++ online submissions for Generate Parentheses.
//time: O(4^n/sqrt(n))
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        if(n == 0) return {""};
        vector<string> ans;
        for(int c = 0; c < n; c++){
            for(string left : generateParenthesis(c)){
                for(string right : generateParenthesis(n-1-c)){
                    ans.push_back("(" + left + ")" + right);
                }
            }
        }
        
        return ans;
    }
};
