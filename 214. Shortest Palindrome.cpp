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

//Rolling hash, Rabin-Karp
//https://leetcode.com/problems/shortest-palindrome/discuss/60153/8-line-O(n)-method-using-Rabin-Karp-rolling-hash
//Runtime: 8 ms, faster than 96.25% of C++ online submissions for Shortest Palindrome.
//Memory Usage: 7.1 MB, less than 98.13% of C++ online submissions for Shortest Palindrome.
class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        
        int MOD = 1e9+7;
        int len = 0;
        //all variable used in multiplication should be declared as "long long"
        long long p;
        long long B = 29;
        long long hash1 = 0, hash2 = 0;
        
        for(int i = 0, p = 1L; i < n; ++i, p = (p * B) % MOD){
            //all variable used in multiplication should be declared as "long long"
            long long d = s[i]-'a';
            hash1 = (hash1 * B + d) % MOD;
            hash2 = (hash2 + d * p) % MOD;
            //the length of palindrome
            if(hash1 == hash2) len = i+1;
        }
        
        string prepend = s.substr(len);
        reverse(prepend.begin(), prepend.end());
        
        return prepend + s; 
    }
};

//Manacher's algorithm
//https://leetcode.com/problems/shortest-palindrome/discuss/60234/Easy-C%2B%2B-Manacher
//Runtime: 12 ms, faster than 61.90% of C++ online submissions for Shortest Palindrome.
//Memory Usage: 7.8 MB, less than 70.16% of C++ online submissions for Shortest Palindrome.
class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        int tn = 2*n+3;
        
        /*
        s: abcd
        t: ^#a#b#c#d#$
        */
        string t(tn, '#');
        
        t[0] = '^';
        t[t.size()-1] = '$';
        
        for(int i = 2, j = 0; j < n; i += 2, ++j){
            t[i] = s[j];
        }
        
        // cout << t << endl;
        
        int mirror = 0, right = 0, center = 0;
        vector<int> p(tn, 0);
        
        for(int i = 0; i < tn; ++i){
            //i - center == center - mirror
            mirror = center*2 - i;
            
            if(i < right){
                p[i] = min(p[mirror], right - i);
            }
            
            while(i+p[i]+1 < tn && i-(p[i]+1) >= 0 && t[i-(p[i]+1)] == t[i+p[i]+1]){
                ++p[i];
            }
            
            if(i+p[i] > right){
                center = i;
                right = center + p[center];
            }
        }
        
        /*
        find in t[1:tn-2]: #a#b#c#d#
        */
        int not_match_start;
        for (int i = tn - 2; i > 0; i--) {
            // cout << i << " - " << p[i] << endl;
            //i: the center of palindrome
            //p[i]: the length of half palindrome in t
            //i - p[i]: the start index of palindrome in t
            //here we choose the palindrome starting at 1?
            if (i - p[i] == 1) {
                not_match_start = p[i];
                break;
            }
        }
        string not_match = s.substr(not_match_start); 
        reverse(not_match.begin(), not_match.end());
        return not_match + s;
    }
};
