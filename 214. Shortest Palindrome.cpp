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

//Approach #2 Two pointers and recursion [Accepted]
//Runtime: 8 ms, faster than 96.25% of C++ online submissions for Shortest Palindrome.
//Memory Usage: 7.2 MB, less than 93.85% of C++ online submissions for Shortest Palindrome.
//time: O(N^2), space: O(N)
class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        
        int i = 0;
        for(int j = n-1; j >= 0; --j){
            if(s[i] == s[j]){
                ++i;
            }
        }
        
        //there are "i(=n)" char matched
        if(i == n) return s;
        
        //the unmatched part
        string remain = s.substr(i);
        string remain_rev = remain;
        reverse(remain_rev.begin(), remain_rev.end());
        
        // cout << "i: " << i << ", " << remain_rev << " + ... + " << remain << endl;
        return remain_rev + shortestPalindrome(s.substr(0, i)) + remain;
    }
};
