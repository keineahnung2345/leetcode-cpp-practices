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
