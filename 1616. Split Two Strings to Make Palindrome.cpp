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

//O(N^2)
//TLE
//76 / 102 test cases passed.
class Solution {
public:
    bool isPalindrome(string s, int start, int end){
        int n = s.size();
        
        for(int i = 0; start+i < end-i; ++i){
            if(s[start+i] != s[end-i]) return false;
        }
        
        return true;
    }
    
    bool checkPalindromeFormation(string a, string b) {
        int n = a.size();
        
        if(isPalindrome(a, 0, n-1) || isPalindrome(b, 0, n-1))
            return true;
        
        int i = 0;
        //a prefix + b suffix
        while(a[i] == b[n-1-i]){
            //split before n-1-i: a[0...i] + a[i+1...n-1-i-1] + b[n-1-i:]
            //split after i     : a[0...i] + b[i+1...n-1-i-1] + b[n-1-i:]
            if(isPalindrome(a, i+1, n-1-i-1)) return true;
            if(isPalindrome(b, i+1, n-1-i-1)) return true;
            ++i;
        }

        i = 0;
        //b prefix + a suffix
        while(b[i] == a[n-1-i]){
            if(isPalindrome(b, i+1, n-1-i-1)) return true;
            if(isPalindrome(a, i+1, n-1-i-1)) return true;
            ++i;
        }
        
        return false;
    }
};

//O(N)
//Runtime: 100 ms, faster than 33.33% of C++ online submissions for Split Two Strings to Make Palindrome.
//Memory Usage: 28.9 MB, less than 16.67% of C++ online submissions for Split Two Strings to Make Palindrome.
class Solution {
public:
    bool isPalindrome(string s, int start, int end){
        int n = s.size();
        
        for(int i = 0; start+i < end-i; ++i){
            if(s[start+i] != s[end-i]) return false;
        }
        
        return true;
    }
    
    pair<int,int> palindromeRange(string s){
        int n = s.size();
        
        /*
        n = 4, (i,j) = (1,2)
        n = 5, (i,j) = (1,3)
        */
        int i = n/2-1, j = n/2+(n%2);
        
        while(i >= 0 && j < n && s[i] == s[j]){
            --i;
            ++j;
        }
        
        return {i+1, j-1};
    }
    
    bool checkPalindromeFormation(string a, string b) {
        int n = a.size();
        
        pair<int, int> apr = palindromeRange(a);
        pair<int, int> bpr = palindromeRange(b);
        
        if(apr.first == 0 || bpr.first == 0)
            return true;
        
        int i = 0;
        //a prefix + b suffix
        while(a[i] == b[n-1-i]){
            //split before n-1-i: a[0...i] + a[i+1...n-1-i-1] + b[n-1-i:]
            //split after i     : a[0...i] + b[i+1...n-1-i-1] + b[n-1-i:]
            if(i+1 >= apr.first) return true;
            if(i+1 >= bpr.first) return true;
            ++i;
        }

        i = 0;
        //b prefix + a suffix
        while(b[i] == a[n-1-i]){
            if(i+1 >= bpr.first) return true;
            if(i+1 >= apr.first) return true;
            ++i;
        }
        
        return false;
    }
};

//O(N) greedy
//https://leetcode.com/problems/split-two-strings-to-make-palindrome/discuss/888885/C%2B%2BJava-Greedy-O(n)-or-O(1)
//Runtime: 76 ms, faster than 50.00% of C++ online submissions for Split Two Strings to Make Palindrome.
//Memory Usage: 24.5 MB, less than 25.00% of C++ online submissions for Split Two Strings to Make Palindrome.
//time: O(N), space: O(1)
class Solution {
public:
    bool isPalindrome(string& s, int i, int j){
        while(i < j && s[i] == s[j]){
            ++i;
            --j;
        }
        
        return i >= j;
    }
    
    bool check(string& a, string& b){
        int n = a.size();
        int i = 0;
        
        /*
        Greedy: match their two sides as more as possible,
        so the middle part is more likely to be a palindrome
        */
        while(i < n-1-i && a[i] == b[n-1-i]){
            ++i;
        }
        
        return i >= n-1-i || isPalindrome(a, i, n-1-i) || isPalindrome(b, i, n-1-i);
    }
    
    bool checkPalindromeFormation(string a, string b) {
        return check(a, b) || check(b, a);
    }
};
