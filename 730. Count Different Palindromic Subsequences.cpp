//DP, O(N^3)
//https://leetcode.com/problems/count-different-palindromic-subsequences/discuss/109507/Java-96ms-DP-Solution-with-Detailed-Explanation
//Runtime: 164 ms, faster than 60.90% of C++ online submissions for Count Different Palindromic Subsequences.
//Memory Usage: 36.4 MB, less than 100.00% of C++ online submissions for Count Different Palindromic Subsequences.
//time: O(N^3), space: O(N^2)
class Solution {
public:
    int countPalindromicSubsequences(string S) {
        int n = S.size();
        const int MOD = 1e9+7;
        // vector<vector<long long>> dp(n, vector(n, 0LL)); //don't need this!!
        vector<vector<int>> dp(n, vector(n, 0));
        
        for(int dist = 0; dist < n; dist++){
            for(int i = 0; i + dist < n; i++){
                int j = i+dist;
                //dp[i][j]: count of palindrome in S[i...j]
                if(i == j){
                    //base case: only one char
                    dp[i][j] = 1;
                    continue;
                }
                
                if(S[i] != S[j]){
                    /*
                    dp[i+1][j-1] is included in both 
                    dp[i][j-1] and dp[i+1][j],
                    so we need to deduce it
                    */
                    dp[i][j] = dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1];
                }else{
                    //S[i] == S[j]
                    int lo = i+1, hi = j-1;
                    
                    /*
                    try to find S[i] in S[i+1...j-1],
                    if found,
                    S[lo] will be the first S[i] in S[i+1...j-1]
                    if not found,
                    lo will > hi
                    */
                    while(lo <= hi && S[lo] != S[i]){
                        lo++;
                    }
                    
                    /*
                    either found: S[hi] will be S[i]
                    or not found: hi < lo
                    */
                    while(lo <= hi && S[hi] != S[i]){
                        hi--;
                    }
                    
                    /*
                    now there are 3 cases:
                    lo > hi: not found S[i] in S[i+1...j-1]
                    lo == hi: only one S[i] in S[i+1...j-1]
                    lo < hi: at least two S[i] in S[i+1...j-1]
                    */
                    
                    if(lo > hi){
                        /*
                        axxxa
                        dp[i+1][j-1]*2: 
                        both the palindrome count in xxx itself and
                        axxxa, so two times
                        
                        +2:
                        we can construct two palindrome with the 2 'a's:
                        'a' and 'aa'
                        note that since there is no 'a' in S[i+1...j-1],
                        so 'a' and 'aa' are not duplicate
                        */
                        dp[i][j] = dp[i+1][j-1]*2+2;
                    }else if(lo == hi){
                        /*
                        axxaxxa
                        dp[i+1][j-1]*2:
                        both the palindrome count in xxaxx itself and
                        axxaxxa, so two times
                        
                        +1:
                        we can construct the palindrome 'aa' 
                        with S[i] and S[j]
                        note that palindrome 'a' will be duplicate since
                        S[i+1...j-1] already contains one 'a'
                        */
                        dp[i][j] = dp[i+1][j-1]*2+1;
                    }else if(lo < hi){
                        /*
                        axxayyaxxa
                        
                        dp[i+1][j-1]*2:
                        both the palindrome count in xxayyaxx itself and
                        axxayyaxxa, so two times
                        
                        -dp[lo+1][hi-1]:
                        when constructing palindrome using the two 'a's
                        (S[i] and S[j]),
                        we may use S[i],S[j] and the yy(S[lo+1...hi-1]),
                        but since the palindrome constructed from
                        S[i],S[j],S[lo+1...hi-1] will be the same of 
                        that constructed from S[lo],S[hi],S[lo+1...hi-1]
                        so we need to subtract dp[lo+1][hi-1] to remove
                        the duplicate
                        */
                        dp[i][j] = dp[i+1][j-1]*2 - dp[lo+1][hi-1];
                    }
                }
                
                /*
                in 
                "dp[i][j] = dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1];"
                or
                "dp[i][j] = dp[i+1][j-1]*2 - dp[lo+1][hi-1];"
                
                because dp[i][j-1], dp[i+1][j], dp[i+1][j-1] and 
                dp[lo+1][hi-1] are after mod operation
                (they are not original value),
                so the subtraction may lead to negative number
                (the negative number doesn't come from integer overflow)
                knowning the reason why negative number appears,
                it's naturally to add the number MOD back!
                */
                dp[i][j] = (dp[i][j] < 0) ? dp[i][j] + MOD: dp[i][j] % MOD;
            }
        }
        
        return dp[0][n-1];
    }
};

//DP, O(N^2)
//optimize the previous method, finding lo and hi in O(1) time
//https://leetcode.com/problems/count-different-palindromic-subsequences/discuss/109507/Java-96ms-DP-Solution-with-Detailed-Explanation/111365
//Runtime: 120 ms, faster than 84.48% of C++ online submissions for Count Different Palindromic Subsequences.
//Memory Usage: 36.7 MB, less than 100.00% of C++ online submissions for Count Different Palindromic Subsequences.
//time: O(N^2), space: O(N^2)
class Solution {
public:
    int countPalindromicSubsequences(string S) {
        int n = S.size();
        const int MOD = 1e9+7;
        vector<vector<int>> dp(n, vector(n, 0));
        
        //record the next right/left position of the same char
        vector<int> nextRight(n), nextLeft(n);
        //helper
        vector<int> char2pos(4, -1);
        
        for(int i = 0; i < n; i++){
            /*
            initial value of char2pos are all -1,
            meaning that we haven't found S[i] in S[0...i-1]
            */
            nextLeft[i] = char2pos[S[i]-'a'];
            /*
            record the position of S[i], 
            this will be used in following iterations
            */
            char2pos[S[i]-'a'] = i;
        }
        
        fill(char2pos.begin(), char2pos.end(), n);
        for(int i = n-1; i >= 0; i--){
            nextRight[i] = char2pos[S[i]-'a'];
            char2pos[S[i]-'a'] = i;
        }
        
        for(int dist = 0; dist < n; dist++){
            for(int i = 0; i + dist < n; i++){
                int j = i+dist;
                if(i == j){
                    dp[i][j] = 1;
                    continue;
                }
                
                if(S[i] != S[j]){
                    dp[i][j] = dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1];
                }else{
                    //the position of S[i] in S[i+1...]
                    int lo = nextRight[i];
                    //the position of S[j] in S[...j-1]
                    int hi = nextLeft[j];
                    /*
                    note that lo and hi could be out of the range of 
                    S[i+1...j-1], but this can be handled by lo > hi
                   */
                    if(lo > hi){
                        dp[i][j] = dp[i+1][j-1]*2+2;
                    }else if(lo == hi){
                        dp[i][j] = dp[i+1][j-1]*2+1;
                    }else if(lo < hi){
                        dp[i][j] = dp[i+1][j-1]*2 - dp[lo+1][hi-1];
                    }
                }
                dp[i][j] = (dp[i][j] < 0) ? dp[i][j] + MOD: dp[i][j] % MOD;
            }
        }
        
        return dp[0][n-1];
    }
};
