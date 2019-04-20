//TLE

class Solution {
public:
    bool rValidPalindrome(string s, int i, int j, int deleted){
        if(i >= j) return true;
        if(s[i] == s[j]){
            return rValidPalindrome(s, i+1, j-1, deleted);
        }else if(s[i+1] != s[j] && s[i] != s[j-1]){
            //we cannot make it valid by deleting a char
            return false;
        }else if(deleted == 1){
            //we must delete one more char now, and it exceeds the limit
            return false;
        }
        //delete one char from former part or latter part
        return rValidPalindrome(s, i+1, j, deleted+1) || rValidPalindrome(s, i, j-1, deleted+1);
    }
    bool validPalindrome(string s) {
        return rValidPalindrome(s, 0, s.size()-1, 0);
    }
};

//Greedy
//Time Complexity: O(N) where N is the length of the string. 
// Each of two checks of whether some substring is a palindrome is O(N).
//Space Complexity: O(1) additional complexity. Only pointers were stored in memory.
//Runtime: 112 ms, faster than 71.55% of C++ online submissions for Valid Palindrome II.
//Memory Usage: 26.1 MB, less than 56.80% of C++ online submissions for Valid Palindrome II.

class Solution {
public:
    bool isPalindromeRange(string s, int i, int j){
        while(i < j){
            if(s[i++] != s[j--]) return false;
        }
        return true;
    }
    bool validPalindrome(string s) {
        for(int i = 0; i < s.size()/2; i++){
            int j = s.size()-1-i;
            if(s[i] != s[j]){
                return isPalindromeRange(s, i+1, j) || 
                    isPalindromeRange(s, i, j-1);
            }
        }
        return true;
    }
};
