//DP
//https://leetcode.com/problems/string-compression-ii/discuss/755970/Python-dynamic-programming
//TLE
//63 / 132 test cases passed.
class Solution {
public:
    int counter(string& s, int cur, char last_char, int last_count, int k){
        if(cur == s.size()) return 0;
        
        if(s[cur] == last_char){
            /*
            we only discard char when we first meet it,
            so here we always keep the char
            */
            int incr = 0;
            if(last_count == 1 || log10(last_count+1) == int(log10(last_count+1))){
                /*
                we need one more digit when the count changes from:
                1->2, 9->10, 99->100
                */
                incr = 1;
            }
            int ret = incr + counter(s, cur+1, s[cur], last_count+1, k);
            // cout << "(" << cur << ", " << last_char << ", " << last_count << ", " << k << ") : " << ret << endl;
            return ret;
        }else{
            /*
            when we meet first such char, 
            we can choose whether to keep it or discard it
            */
            //add 1: current char is the first char of its kind, and it takes one position in the encoded string
            int keep_count = 1 + counter(s, cur+1, s[cur], 1, k);
            //current char deleted, so last_char and last_count remain unchanged
            //k < 0 is impossible, early stopping
            int discard_count = (k >= 1) ? counter(s, cur+1, last_char, last_count, k-1) : numeric_limits<int>::max();
            
            int ret = min(keep_count, discard_count);
            // cout << "(" << cur << ", " << last_char << ", " << last_count << ", " << k << ") : " <<  ret << endl;
            return ret;
        }
    };
    
    int getLengthOfOptimalCompression(string s, int k) {
        int n = s.size();
        
        return counter(s, 0, '#', 0, k);
    }
};

//DP with memorization
//https://leetcode.com/problems/string-compression-ii/discuss/755762/C%2B%2B-top-down-dynamic-programming-with-explanation
//TLE
//87 / 132 test cases passed.
class Solution {
public:
    vector<vector<vector<vector<int>>>> memo;
    
    int counter(string& s, int cur, char last_char, int last_count, int k){
        if(cur == s.size()) return 0;
        
        if(memo[cur][last_char-'a'][last_count][k] != -1){
            return memo[cur][last_char-'a'][last_count][k];
        }
        
        if(s[cur] == last_char){
            int incr = 0;
            if(last_count == 1 || log10(last_count+1) == int(log10(last_count+1))){
                incr = 1;
            }
            memo[cur][last_char-'a'][last_count][k] = incr + counter(s, cur+1, s[cur], last_count+1, k);
        }else{
            int keep_count = 1 + counter(s, cur+1, s[cur], 1, k);
            int discard_count = (k >= 1) ? counter(s, cur+1, last_char, last_count, k-1) : numeric_limits<int>::max();
            
            memo[cur][last_char-'a'][last_count][k] = min(keep_count, discard_count);
        }
        
        return memo[cur][last_char-'a'][last_count][k];
    };
    
    int getLengthOfOptimalCompression(string s, int k) {
        int n = s.size();
        
        memo = vector<vector<vector<vector<int>>>>(n, vector<vector<vector<int>>>(26+1, vector<vector<int>>(n, vector<int>(k+1, -1))));
        
        //'{' is the char just after 'z'
        return counter(s, 0, '{', 0, k);
    }
};

//DP with memorization, prune
//https://leetcode.com/problems/string-compression-ii/discuss/755762/C%2B%2B-top-down-dynamic-programming-with-explanation
//Runtime: 1168 ms, faster than 22.58% of C++ online submissions for String Compression II.
//Memory Usage: 450.5 MB, less than 5.12% of C++ online submissions for String Compression II.
class Solution {
public:
    vector<vector<vector<vector<int>>>> memo;
    
    int counter(string& s, int cur, char last_char, int last_count, int k){
        if(cur == s.size()) return 0;
        
        if(memo[cur][last_char-'a'][last_count][k] != -1){
            return memo[cur][last_char-'a'][last_count][k];
        }
        
        if(s[cur] == last_char){
            int incr = 0;
            if(last_count == 1 || last_count == 9){
                incr = 1;
            }
            //set the upper limit of "last_count" as 10
            memo[cur][last_char-'a'][last_count][k] = incr + counter(s, cur+1, s[cur], min(10, last_count+1), k);
        }else{
            int keep_count = 1 + counter(s, cur+1, s[cur], 1, k);
            int discard_count = (k >= 1) ? counter(s, cur+1, last_char, last_count, k-1) : numeric_limits<int>::max();
            
            memo[cur][last_char-'a'][last_count][k] = min(keep_count, discard_count);
        }
        
        return memo[cur][last_char-'a'][last_count][k];
    };
    
    int getLengthOfOptimalCompression(string s, int k) {
        int n = s.size();
        
        if(n == 100 && k == 0){
            char c = s[0];
            if(s == string(c, 100)){
                /*
                this is the only case that "last_count" could be 100,
                and now we exclude it
                */
                return 4;
            }
        }
        
        /*
        now the max value "last_count" could be is 99,
        and we know that when "last_count" is in [10,99],
        the encoded string will have same length,
        so we don't care "last_count" once it reaches 10
        */
        
        memo = vector<vector<vector<vector<int>>>>(n, vector<vector<vector<int>>>(26+1, vector<vector<int>>(11, vector<int>(k+1, -1))));
        
        return counter(s, 0, '{', 0, k);
    }
};

//DP with memorization, prune, use array instead of vector
//https://leetcode.com/problems/string-compression-ii/discuss/755762/C%2B%2B-top-down-dynamic-programming-with-explanation
//Runtime: 376 ms, faster than 45.89% of C++ online submissions for String Compression II.
//Memory Usage: 19.2 MB, less than 49.55% of C++ online submissions for String Compression II.
class Solution {
public:
    int memo[100][27][11][101];
    
    int counter(string& s, int cur, char last_char, int last_count, int k){
        if(cur == s.size()) return 0;
        
        if(memo[cur][last_char-'a'][last_count][k] != -1){
            return memo[cur][last_char-'a'][last_count][k];
        }
        
        if(s[cur] == last_char){
            int incr = 0;
            if(last_count == 1 || last_count == 9){
                incr = 1;
            }
            memo[cur][last_char-'a'][last_count][k] = incr + counter(s, cur+1, s[cur], min(10, last_count+1), k);
        }else{
            int keep_count = 1 + counter(s, cur+1, s[cur], 1, k);
            int discard_count = (k >= 1) ? counter(s, cur+1, last_char, last_count, k-1) : numeric_limits<int>::max();
            
            memo[cur][last_char-'a'][last_count][k] = min(keep_count, discard_count);
        }
        
        return memo[cur][last_char-'a'][last_count][k];
    };
    
    int getLengthOfOptimalCompression(string s, int k) {
        int n = s.size();
        
        if(n == 100 && k == 0){
            char c = s[0];
            if(s == string(c, 100)){
                /*
                this is the only case that "last_count" could be 100,
                and now we exclude it
                */
                return 4;
            }
        }
        
        /*
        now the max value "last_count" could be is 99,
        and we know that when "last_count" is in [10,99],
        the encoded string will have same length,
        so we don't care "last_count" once it reaches 10
        */
        
        for(int a = 0; a < n; ++a){
            for(int b = 0; b <= 26; ++b){
                for(int c = 0; c <= 10; ++c){
                    for(int d = 0; d <= n; ++d){
                        memo[a][b][c][d] = -1;
                    }
                }
            }
        }
        
        return counter(s, 0, '{', 0, k);
    }
};
