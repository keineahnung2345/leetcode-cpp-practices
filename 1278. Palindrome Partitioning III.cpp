//Runtime: 16 ms, faster than 72.66% of C++ online submissions for Palindrome Partitioning III.
//Memory Usage: 6.6 MB, less than 100.00% of C++ online submissions for Palindrome Partitioning III.
//https://leetcode.com/problems/palindrome-partitioning-iii/discuss/441427/Python3-Top-down-DFS-with-Memoization
class Solution {
public:
    vector<vector<int>> memo;
    int n;
    
    int cost(string& s, int start, int end){
        int res = 0;
        /*
        exit when the remaining part has 0 or 1 char,
        that is, start == end(only 1 char) or 
        start > end(only 0 char)
        */
        for(; start < end; start++, end--){
            if(s[start] != s[end]) res++;
        }
        return res;
    }
    
    int dfs(string& s, int start, int k){
        if(memo[start][k] != INT_MAX){
            return memo[start][k];
        }
        
        /*
        the problem doesn't allow k > s.size(),
        so we can just use == here,
        if the limit doesn't exist,
        we need <= here
        */
        // if(n - start <= k){
        if(n - start == k){
            /*
            the current string to be partitioned is
            s[start, n-1], and its length is n-start,
            if the length is (less than or) equal to k,
            we can partition it to k parts and 
            each part having length 1,
            so the cost will be 0
            */
            return 0;
        }
        
        if(k == 1){
            //can't be partitioned anymore
            return cost(s, start, n-1);
        }
        
        /*
        next <= n-k+1:
        looing at dfs(s, next, k-1),
        next will be n-k+1 and k will be k-1,
        so in next recursion,
        n - start == k will holds and return 0,
        this is the base where we can split the remaing string into k parts
        */
        // for(int next = start+1; next <= n-k+1; next++){
        // for(int next = start+1; next <= n-1; next++){ //must be used with if(n - start <= k){
            memo[start][k] = min(memo[start][k], cost(s, start, next-1)+dfs(s, next, k-1));
        }
        
        return memo[start][k];
    }
    
    int palindromePartition(string s, int k) {
        n = s.size();
        //padding for k's dimension, index 0 is meaningless
        memo = vector<vector<int>>(n, vector(k+1, INT_MAX));
        
        return dfs(s, 0, k);
    }
};
