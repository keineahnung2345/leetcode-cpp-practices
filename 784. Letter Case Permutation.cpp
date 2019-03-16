/**
Given a string S, we can transform every letter individually to be lowercase or uppercase to create another string.  Return a list of all possible strings we could create.

Examples:
Input: S = "a1b2"
Output: ["a1b2", "a1B2", "A1b2", "A1B2"]

Input: S = "3z4"
Output: ["3z4", "3Z4"]

Input: S = "12345"
Output: ["12345"]
Note:

S will be a string with length between 1 and 12.
S will consist only of letters or digits.
**/

//Runtime: 20 ms, faster than 29.58% of C++ online submissions for Letter Case Permutation.
//Memory Usage: 13.6 MB, less than 53.00% of C++ online submissions for Letter Case Permutation.
class Solution {
public:
    vector<string> letterCasePermutation(string S) {
        vector<string> ans;
        ans.push_back(S);
        
        for(int i = 0; i < S.size(); i++){
            char c = S[i];
            if(isalpha(c)){
                vector<string> tmpv;
                for(string prevS : ans){
                    string tmp(prevS.begin(), prevS.end());
                    if(islower(c)){
                        tmp[i] = toupper(c);
                    }else if(isupper(c)){
                        tmp[i] = tolower(c);
                    }
                    tmpv.push_back(tmp);
                }
                //concatenate
                ans.insert(ans.end(), tmpv.begin(), tmpv.end());
            }
        }
        
        return ans;
    }
};
