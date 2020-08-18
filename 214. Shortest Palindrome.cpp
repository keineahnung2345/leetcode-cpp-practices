//Brute force
//TLE
//119 / 120 test cases passed.
class Solution {
public:
    bool isPalindrome(string s){
        int n = s.size();
        
        for(int i = 0; i < n-1-i; ++i){
            if(s[i] != s[n-1-i]){
                return false;
            }
        }
        
        return true;
    };
    
    string shortestPalindrome(string s) {
        int n = s.size();
        
        for(int l = n; l >= 1; --l){
            if(isPalindrome(s.substr(0, l))){
                string prepend = s.substr(l);
                reverse(prepend.begin(), prepend.end());
                return prepend + s;
            }
        }
        
        return "";
    }
};

//Approach #1 Brute force [Accepted]
//TLE
//119 / 120 test cases passed.
//time: O(N^2), space: O(N)
class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        string srev(s.rbegin(), s.rend());
        
        /*
        s:    "aacecaaa"
        srev: "aaacecaa"
        */
        for(int l = n; l >= 1; --l){
            if(s.substr(0, l) == srev.substr(n-l)){
                return srev.substr(0, n-l) + s;
            }
        }
        
        return "";
    }
};
