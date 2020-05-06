//Recursive
//TLE
//21 / 29 test cases passed.
class Solution {
public:
    bool isPalindrome(string s){
        int n = s.size();
        for(int i = 0; i < s.size()/2; i++){
            if(s[i] != s[n-1-i]) return false;
        }
        return true;
    };
    
    int minCut(string s) {
        int ans = 0;
        if(!isPalindrome(s)){
            // cout << s << endl;
            if(s.size() == 2) return 1;
            ans = INT_MAX;
            for(int i = 1; i < s.size(); i++){
                ans = min(ans, minCut(s.substr(0, i)) + minCut(s.substr(i)));
            }
            ans++;
        }
        return ans;
    }
};
