//Approach 3: Dynamic Programming
//https://ithelp.ithome.com.tw/articles/10215365
//Runtime: 924 ms, faster than 6.44% of C++ online submissions for Longest Palindromic Substring.
//Memory Usage: 24.3 MB, less than 21.38% of C++ online submissions for Longest Palindromic Substring.
//time: O(N^2), space: O(N^2)
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n, vector(n, false));
        string ans;
        
        for(int i = n-1; i >= 0; i--){
            for(int j = i; j < n; j++){
                //susbstring: s[i...j]
                //length 1
                if(i == j){
                    dp[i][j] = true;
                }else if(i+1 == j){
                    dp[i][j] = (s[i] == s[j]);
                }else{
                    dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1];
                }
                
                if(dp[i][j] && j-i+1 > ans.size()){
                    ans = s.substr(i, j-i+1);
                }
            }
        }
        
        return ans;
    }
};

//same as above, space complexity O(n)
//Runtime: 904 ms, faster than 7.04% of C++ online submissions for Longest Palindromic Substring.
//Memory Usage: 14.6 MB, less than 40.00% of C++ online submissions for Longest Palindromic Substring.
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        vector<vector<bool>> dp(2, vector(n, false));
        string ans;
        
        for(int i = n-1; i >= 0; i--){
            for(int j = i; j < n; j++){
                //susbstring: s[i...j]
                //length 1
                if(i == j){
                    dp[i%2][j] = true;
                }else if(i+1 == j){
                    dp[i%2][j] = (s[i] == s[j]);
                }else{
                    dp[i%2][j] = (s[i] == s[j]) && dp[(i+1)%2][j-1];
                }
                
                if(dp[i%2][j] && j-i+1 > ans.size()){
                    ans = s.substr(i, j-i+1);
                }
            }
        }
        
        return ans;
    }
};

//Approach 1: Longest Common Substring
//https://www.geeksforgeeks.org/longest-common-substring-dp-29/
//Runtime: 664 ms, faster than 10.25% of C++ online submissions for Longest Palindromic Substring.
//Memory Usage: 191.6 MB, less than 5.51% of C++ online submissions for Longest Palindromic Substring.
//time: O(N^2), space: O(N^2)
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        string rs(s.rbegin(), s.rend());
        string ans = "";
        
        //find s and rs's longest common substring
        
        vector<vector<int>> dp(n+1, vector(n+1, 0));
        
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(s[i-1] == rs[j-1]){
                    dp[i][j] = dp[i-1][j-1] + 1;
                }else{
                    dp[i][j] = 0;
                }
                
                /*
                the additional condition turns the problem from
                longest common substring to longest palindrome,
                because it restricts the position of lc substring
                */
                if(dp[i][j] > ans.size() && i+j == dp[i][j]+n){
                    //s[i-dp[i][j]...i] = sr[j-dp[i][j]...j]
                    // cout << s.substr(i-dp[i][j], dp[i][j]) << ", " << rs.substr(j-dp[i][j], dp[i][j]) << endl;
                    ans = s.substr(i-dp[i][j], dp[i][j]);
                }
            }
        }
        
        return ans;
    }
};

//same as above, space complexity O(n)
//Runtime: 652 ms, faster than 10.41% of C++ online submissions for Longest Palindromic Substring.
//Memory Usage: 14.5 MB, less than 40.00% of C++ online submissions for Longest Palindromic Substring.
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        string rs(s.rbegin(), s.rend());
        string ans = "";
        
        vector<vector<int>> dp(2, vector(n+1, 0));
        
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(s[i-1] == rs[j-1]){
                    dp[i%2][j] = dp[(i+1)%2][j-1] + 1;
                }else{
                    dp[i%2][j] = 0;
                }
                
                if(dp[i%2][j] > ans.size() && i+j == dp[i%2][j]+n){
                    ans = s.substr(i-dp[i%2][j], dp[i%2][j]);
                }
            }
        }
        
        return ans;
    }
};

//Approach 4: Expand Around Center
//Runtime: 84 ms, faster than 52.27% of C++ online submissions for Longest Palindromic Substring.
//Memory Usage: 102.1 MB, less than 18.62% of C++ online submissions for Longest Palindromic Substring.
//time: O(N^2), space: O(1)
class Solution {
public:
    int expandAroundCenter(string s, int l, int r){
        //s[l...r], both inclusive
        while(l >= 0 && r < s.size() && s[l] == s[r]){
            l--;
            r++;
        }
        
        //return to previous valid status
        l++; r--;
        
        return r-l+1;
    };
    
    string longestPalindrome(string s) {
        if(s.size() == 0) return "";
        int start = 0, end = 0;
        for(int i = 0; i < s.size(); i++){
            int len1 = expandAroundCenter(s, i, i);
            int len2 = expandAroundCenter(s, i, i+1);
            int len = max(len1, len2);
            // cout << "len: " << len1 << ", " << len2 << endl;
            if(len > end-start+1){
                /*
                for odd len:
                (len-1)/2 and len/2 are the same
                
                for even len:
                (len-1)/2 = len/2 -1,
                i.e. [i-(x-1), i, i+1, i+x]
                */
                start = i - (len-1)/2;
                end = i + len/2;
                // cout << "[" << start << ", " << end << "]" << endl;
            }
        }
        // cout << "================" << endl;
        return s.substr(start, end-start+1);
    }
};

//Approach 5: Manacher's Algorithm
//https://www.youtube.com/watch?v=nbTSfrEfo6M&feature=emb_logo
//Runtime: 8 ms, faster than 94.20% of C++ online submissions for Longest Palindromic Substring.
//Memory Usage: 7.6 MB, less than 100.00% of C++ online submissions for Longest Palindromic Substring.
//time: O(n), space: O(n)
class Solution {
public:
    string longestPalindrome(string s) {
        string t(1, '^');
        
        for(int i = 0; i < s.size(); i++){
            t += '#'; t += s[i];
        }
        
        t += '#'; t += '$';
        
        // cout << t << endl;
        
        vector<int> p(t.size(), 0);
        int mirror = 0;
        int center = 0;
        int right = 0;
        int maxStart = 0;
        
        for(int i = 0; i < t.size(); i++){
            //update mirror
            mirror = 2 * center - i;
            
            /*
            only if current position < last palindrome's right boundary,
            we can use the mirror property of that palindrome
            */
            if(i < right){
                /*
                p[i] is supposed to be same as p[mirror],
                but it's also restricted by 
                the distance to the palindrome's right boundary(right-i)
                */
                p[i] = min(p[mirror], right - i);
            }
            
            /*
            try to expand it:
            try assume the new p[i] is 1+p[i], and see if it works
            
            i+(1+p[i]) < t.size() && i-(1+p[i]) >= 0: 
            the expected new palindrome's range is [i-p[i],i+p[i]],
            we need to check if it falls in [0, t.size())
            */
            while(i+(1+p[i]) < t.size() && i-(1+p[i]) >= 0 && t[i+(1+p[i])] == t[i-(1+p[i])]){
                p[i]++;
            }
            
            //update ans
            if(p[i] > p[maxStart]){
                maxStart = i;
            }
            
            // cout << "i: " << i << ", center: " << center << ", mirror: " << mirror << ", p[i]: " << p[i] << endl;
            
            /*
            find a palindrome whose right boundary exceeds 
            the old palindrome's right boundary,
            so update the variables "right" and "center" which
            are related to palindrome
            */
            if(i+p[i] > right){
                right = i+p[i];
                center = i;
            }
        }
        
        // cout << "i: " << maxStart << ", p[i]: " << p[maxStart] << endl;
        
        return s.substr((maxStart-p[maxStart])/2, p[maxStart]);
    }
};
