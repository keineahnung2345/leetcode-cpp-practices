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
