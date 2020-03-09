//TLE
class Solution {
public:
    bool isPalindrome(string s){
        int N = s.size();
        
        //get the last half of s
        string s_rvs = s.substr(N - N/2);
        reverse(s_rvs.begin(), s_rvs.end());
        
        return s.substr(0, N/2) == s_rvs;
    };
    
    void backtrack(vector<vector<string>>& parts, vector<string>& part, string s, int start){
        if(start >= s.size()){
            bool flag = true;
            for(string token : part){
                if(!isPalindrome(token)){
                    flag = false;
                    break;
                }
            }
            if(flag) parts.push_back(part);
        }else{
            for(int i = 1; start + i <= s.size(); i++){
                // cout << start << " : " << start+i << endl;
                string token = s.substr(start, i);
                part.push_back(token);
                backtrack(parts, part, s, start+i);
                part.pop_back();
            }
        }
    };
    
    vector<vector<string>> partition(string s) {
        int N = s.size();
        vector<vector<string>> parts;
        vector<string> part;
        
        backtrack(parts, part, s, 0);
        
        return parts;
    }
};

//Backtracking with speed up
//https://leetcode.com/problems/permutations/discuss/18239/A-general-approach-to-backtracking-questions-in-Java-(Subsets-Permutations-Combination-Sum-Palindrome-Partioning)
//Runtime: 60 ms, faster than 32.04% of C++ online submissions for Palindrome Partitioning.
//Memory Usage: 24.7 MB, less than 83.33% of C++ online submissions for Palindrome Partitioning.
class Solution {
public:
    bool isPalindrome(string s){
        int N = s.size();
        
        bool flag = true;
        for(int i = 0; i < N/2; i++){
            //N-1-i: left index + right index must equal to N-1
            if(s[i] != s[N-1-i])
                flag = false;
        }
        return flag;
    };
    
    void backtrack(vector<vector<string>>& parts, vector<string>& part, string s, int start){
        if(start >= s.size()){
            parts.push_back(part);
        }else{
            for(int i = 1; start + i <= s.size(); i++){
                string token = s.substr(start, i);
                // cout << start << " : " << start+i << " " << token << endl;
                //to speed up, skip upon meeting a token which is not palindrome
                if(!isPalindrome(token)) continue;
                part.push_back(token);
                backtrack(parts, part, s, start+i);
                part.pop_back();
            }
        }
    };
    
    vector<vector<string>> partition(string s) {
        int N = s.size();
        vector<vector<string>> parts;
        vector<string> part;
        
        backtrack(parts, part, s, 0);
        
        return parts;
    }
};
