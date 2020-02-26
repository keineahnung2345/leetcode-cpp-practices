//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Remove Palindromic Subsequences.
//Memory Usage: 8.5 MB, less than 100.00% of C++ online submissions for Remove Palindromic Subsequences.

class Solution {
public:
    int removePalindromeSub(string s) {
        if(s.empty()) return 0;
        if(string(s.rbegin(), s.rend()) == s) return 1;
        return 2;
    }
};
