//Runtime: 440 ms, faster than 8.71% of C++ online submissions for License Key Formatting.
//Memory Usage: 10 MB, less than 100.00% of C++ online submissions for License Key Formatting.

class Solution {
public:
    string licenseKeyFormatting(string S, int K) {
        //to upper
        transform(S.begin(), S.end(), S.begin(), [](unsigned char c){return toupper(c);});
        
        //remove all '-'
        S.erase(remove_if(S.begin(), S.end(),
                          [](char c) { return c == '-';}),
                S.end());
        
        //start from K pos before S's end
        //end before S's start
        for(int i = S.size()-K; i > 0; i-=K){
            S.insert(S.begin()+i, '-');
        }
        
        return S;
    }
};

//https://leetcode.com/problems/license-key-formatting/discuss/96512/Java-5-lines-clean-solution
//Runtime: 12 ms, faster than 77.39% of C++ online submissions for License Key Formatting.
//Memory Usage: 10.4 MB, less than 82.76% of C++ online submissions for License Key Formatting.
class Solution {
public:
    string licenseKeyFormatting(string S, int K) {
        string ans = "";

        for (int i = S.size() - 1; i >= 0; i--){
            if (S[i] != '-'){
                //need a '-' so that ans.size() is multiple of (K+1)
                if(ans.size() % (K + 1) == K) ans += '-';
                ans += S[i];
            }
        }
        
        reverse(ans.begin(), ans.end());
        transform(ans.begin(), ans.end(), ans.begin(), [](unsigned char c){return toupper(c);});

        return ans;
    }
};
