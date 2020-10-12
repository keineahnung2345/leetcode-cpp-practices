//naive O(N^2)
//TLE
//65 / 102 test cases passed.
class Solution {
public:
    bool isPalindrome(string s){
        int n = s.size();
        
        for(int i = 0; i < n-1-i; ++i){
            if(s[i] != s[n-1-i]) return false;
        }
        
        return true;
    }
    
    bool checkPalindromeFormation(string a, string b) {
        int n = a.size();
        
        if(isPalindrome(a) || isPalindrome(b)) return true;
        
        for(int i = 1; i < n; ++i){
            //prefix min length: 1
            //suffix min length: 1
            if(isPalindrome(a.substr(0, i) + b.substr(i))) return true;
            if(isPalindrome(b.substr(0, i) + a.substr(i))) return true;
        }
        
        return false;
    }
};
