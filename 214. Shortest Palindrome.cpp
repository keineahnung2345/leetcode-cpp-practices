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

//Approach #3 KMP [Accepted]
//Runtime: 8 ms, faster than 96.25% of C++ online submissions for Shortest Palindrome.
//Memory Usage: 8.2 MB, less than 19.45% of C++ online submissions for Shortest Palindrome.
//time: O(N), space: O(N)
class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        string srev(s.rbegin(), s.rend());
        string snew = s + "#" + srev;
        int nnew = snew.size();
        vector<int> lps(nnew, 0);
        
        // cout << "snew: " << snew << endl;
        for(int i = 1, len = 0; i < nnew; /*no i++ here!*/){
            // cout << "i: " << i << " ";
            if(snew[i] == snew[len]){
                // cout << i << " and " << len << " match" << endl;
                ++len;
                lps[i] = len;
                ++i;
            }else{
                if(len > 0){
                    //fallback
                    // cout << "fallback from " << len << " to " << lps[len-1] << endl;
                    len = lps[len-1];
                }else{
                    // cout << "move i forward" << endl;
                    lps[i] = 0;
                    ++i;
                }
            }
        }
        
        // for(int i = 0; i < nnew; ++i){
        //     cout << "lps[" << i << "]: " << lps[i] << endl; 
        // }
        
        /*
        for s: aacecaaa, (n = 8)
        snew: aacecaaa#aaacecaa (nnew = 17)
        "aacecaa" starting from 0 match "aacecaa" starting from 10,
        i.e. for the srev "aaacecaa", it starts the match from its index 1.
        Note that lps[nnew-1] is 7(the former 7 chars of s match the later 7 chars of srev).
        So we only need one more char to make "s" a palindrome
        */
        return srev.substr(0, n - lps[nnew-1]) + s;
    }
};

//Approach #3 KMP [Accepted](official)
//Runtime: 8 ms, faster than 96.25% of C++ online submissions for Shortest Palindrome.
//Memory Usage: 7.9 MB, less than 66.73% of C++ online submissions for Shortest Palindrome.
class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        string srev(s.rbegin(), s.rend());
        string snew = s + "#" + srev;
        int nnew = snew.size();
        vector<int> lps(nnew, 0);
        
        for(int i = 1; i < nnew; ++i){
            int len = lps[i-1];
            while(len > 0 && snew[i] != snew[len]){
                len = lps[len-1];
            }
            if(snew[i] == snew[len]){
                ++len;
            }
            lps[i] = len;
        }
        return srev.substr(0, n - lps[nnew-1]) + s;
    }
};
