//Approach #1: Brute Force
//TLE
//42 / 58 test cases passed.
//time: O(N*(3^N)), 3^N possible strings, check each string takes O(N)
//space: O(N)
class Solution {
public:
    bool ans;
    
    bool valid(string s){
        int balance = 0;
        for(char c : s){
            switch(c){
                case '(':
                    balance++;
                    break;
                case ')':
                    balance--;
            }
            //in any prefix, we cannot have more ) than (
            if(balance < 0) break;
        }
        return balance == 0;
    };
    
    void solve(string s, int i){
        if(i == s.size()){
            ans |= valid(s);
        }else if(s[i] == '*'){
            //interpret '*' as '(' or ')'
            for(char c : "()"){
                s[i] = c;
                solve(s, i+1);
                if(ans) return;
            }
        }else{
            solve(s, i+1);
        }
    };
    
    bool checkValidString(string s) {
        ans = false;
        solve(s, 0);
        return ans;
    }
};

//Approach #2: Dynamic Programming
//Runtime: 44 ms, faster than 10.48% of C++ online submissions for Valid Parenthesis String.
//Memory Usage: 6.7 MB, less than 100.00% of C++ online submissions for Valid Parenthesis String.
//time: O(N^3), space: O(N^2)
class Solution {
public:
    bool checkValidString(string s) {
        int N = s.size();
        if(N == 0) return true;
        vector<vector<bool>> dp(N, vector<bool>(N, false));
        
        //base case
        for(int i = 0; i < N; i++){
            if(s[i] == '*'){
                dp[i][i] = true;
                // cout << "[" << i << ", " << i << "]" << endl;
                // cout << "true" << endl;
            }
            if(i < N-1 && 
                 (s[i] == '(' || s[i] == '*') &&
                 (s[i+1] == ')' || s[i+1] == '*')){
                //i-1 and i can form a pair of ()
                dp[i][i+1] = true;
                // cout << "[" << i << ", " << i+1 << "]" << endl;
                // cout << "true" << endl;
            }
        }
        
        for(int width = 2; width < N; width++){
            for(int start = 0; start + width < N; start++){
                // cout << "[" << start << ", " << start+width << "]" << endl;
                if(s[start] == '*' && dp[start+1][start+width]){
                    dp[start][start+width] = true;
                    // cout << "true" << endl;
                }else if(s[start] == '(' || s[start] == '*'){
                    //find ')' or '*' in [start+1:start+width]
                    for(int k = start+1; k <= start+width; k++){
                        //s[start] and s[k] makes a pair
                        //dp[start+1][k-1] and dp[k+1][k+wdith] should be valid
                        if((s[k] == ')' || s[k] == '*') &&
                           (k == start+1 || dp[start+1][k-1]) &&
                           (k == start+width || dp[k+1][start+width])){
                            dp[start][start+width] = true;
                            // cout << "true" << endl;
                        }
                    }
                }
            }
        }
        
        return dp[0][N-1];
    }
};
