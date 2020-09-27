//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Letter Combinations of a Phone Number.
//Memory Usage: 6.8 MB, less than 34.49% of C++ online submissions for Letter Combinations of a Phone Number.
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return vector<string>();
        
        vector<string> digit2letters(10);
        
        digit2letters[2] = "abc";
        digit2letters[3] = "def";
        digit2letters[4] = "ghi";
        digit2letters[5] = "jkl";
        digit2letters[6] = "mno";
        digit2letters[7] = "pqrs";
        digit2letters[8] = "tuv";
        digit2letters[9] = "wxyz";
        
        vector<string> ans = {""};
        
        for(const char& c : digits){
            int d = c-'0';
            vector<string> olds = ans;
            ans.clear();
            for(const string& old : olds){
                for(const char& c : digit2letters[d]){
                    ans.push_back(old+c);
                }
            }
        }
        
        return ans;
    }
};

//backtracking
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Letter Combinations of a Phone Number.
//Memory Usage: 6.8 MB, less than 36.51% of C++ online submissions for Letter Combinations of a Phone Number.
//N: number of digits in "digits" mapping to 3 chars, M: number of digits in "digits" mapping to 4 chars
//time: O(3^N * 4^M), space: O(3^N * 4^M)
class Solution {
public:
    vector<string> digit2letters;
    vector<string> ans;
    
    void backtrack(string& comb, string next_digits){
        if(next_digits.empty()){
            ans.push_back(comb);
        }else{
            for(const char& c : digit2letters[next_digits[0]-'0']){
                comb += c;
                backtrack(comb, next_digits.substr(1));
                comb.pop_back();
            }
        }
    }
    
    vector<string> letterCombinations(string digits) {
        digit2letters = vector<string>(10);
        digit2letters[2] = "abc";
        digit2letters[3] = "def";
        digit2letters[4] = "ghi";
        digit2letters[5] = "jkl";
        digit2letters[6] = "mno";
        digit2letters[7] = "pqrs";
        digit2letters[8] = "tuv";
        digit2letters[9] = "wxyz";
        
        if(digits.empty()) return vector<string>();
        
        string comb = "";
        backtrack(comb, digits);
        
        return ans;
    }
};
