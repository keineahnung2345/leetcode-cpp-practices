//Runtime: 4 ms, faster than 88.52% of C++ online submissions for Longest Chunked Palindrome Decomposition.
//Memory Usage: 10.1 MB, less than 100.00% of C++ online submissions for Longest Chunked Palindrome Decomposition.
class Solution {
public:
    int longestDecomposition(string text) {
        int start = 0, N = text.size();
        int ans = 0;
        
        // cout << "N: " << N << endl;
        
        /*
        for even N, say 4, start should be in [0,1]
        for odd N, say 3, start should be in [0,1] (the middle element should also be start once)
        */
        while(start < (N+1)/2){
            int width = 1;
            /*
            current substring ends at start+width-1, 
            for odd N, say 3, ends at 0 or 1
            for even N, say 4, ends at 0 or 1
            */
            while(start + width < (N+1)/2 && 
                  text.substr(start, width) != text.substr(N-start-width, width)){
                // cout << width <<" "<< text.substr(start, width) << " " << text.substr(N-start-width, width) << endl;
                width++;
            }
            // cout << width <<" "<< text.substr(start, width) << " " << text.substr(N-start-width, width) << endl;
            
            /*
            if start + width >= (N+1)/2, that means current substring ends at the middle for odd N (or just before the middle for even N)
            */
            if((text.substr(start, width) == text.substr(N-start-width, width)) && (start != N-start-width)){
                //the two parts are the same and they are different part in original string
                //tokens in both ends
                ans+=2;
            }else{
                //we come to half
                // cout << start << " " << width << " " << N/2 <<endl;
                ans++;
            }
            
            start += width;
        }
        
        return ans;
    }
};

//Rolling hash, Rabin Karp algorithm, two pointer
//https://leetcode.com/problems/longest-chunked-palindrome-decomposition/discuss/350711/Close-to-O(n)-Python-Rabin-Karp-Algorithm-with-two-pointer-technique-with-explanation-(~40ms)
//Runtime: 4 ms, faster than 88.66% of C++ online submissions for Longest Chunked Palindrome Decomposition.
//Memory Usage: 6.6 MB, less than 81.82% of C++ online submissions for Longest Chunked Palindrome Decomposition.
class Solution {
public:
    int power(int x, unsigned int y, unsigned int m){ 
        if (y == 0) 
            return 1; 
        long long p = power(x, y/2, m) % m; 
        p = (p * p) % m; 

        return (y%2 == 0)? p : (x * p) % m; 
    };
    
    int longestDecomposition(string text) {
        int magic_prime = 107;
        int low = 0, high = text.size()-1;
        int cur_low_hash = 0, cur_high_hash = 0, cur_hash_length = 0;
        int ans = 0;
        
        while(low < high){
            /*
            construct a substring from the beginning by appending text[low],
            and cur_low_hash is its hash value,
            note that the newest char has smallest multiplier
            */
            cur_low_hash = (cur_low_hash * 26)%magic_prime;
            cur_low_hash += (text[low]-'a');
            cur_low_hash %= magic_prime;
            
            //pow(26, cur_hash_length) cannot give corrent result even if using long long int in C++
            /*
            construct a substring from the end by appending text[high],
            and cur_high_hash is its hash value,
            note that the newest char has largest multiplier
            */
            cur_high_hash += (text[high]-'a')*(power(26, cur_hash_length, magic_prime));
            cur_high_hash %= magic_prime;
            
            //move the two pointers
            low++;
            high--;
            //the length of the substring represented by cur_low_hash and cur_high_hash
            cur_hash_length++;
            
            /*
            first compare the two substrings' hash values,
            if they are equal, then compare the two substrings themselves
            */
            if(cur_low_hash == cur_high_hash && text.substr(low-cur_hash_length, cur_hash_length) == text.substr(high+1, cur_hash_length)){
                //found two more groups
                ans += 2;
                //reset the states
                cur_low_hash = 0;
                cur_high_hash = 0;
                cur_hash_length = 0;
            }
        }
        
        //edge case 1: only leave a char in the middle(odd N)
        //edge case 2: cannot find palindrome pair on two sides of the middle(even N)
        if((cur_hash_length == 0 && low == high) || cur_hash_length > 0){
            ans++;
        }
        
        return ans;
    }
};

//DP
//https://leetcode.com/problems/longest-chunked-palindrome-decomposition/discuss/351919/Java-DP-Solution.-Straight-Forward-With-Explanation
//Runtime: 600 ms, faster than 5.44% of C++ online submissions for Longest Chunked Palindrome Decomposition.
//Memory Usage: 461.4 MB, less than 100.00% of C++ online submissions for Longest Chunked Palindrome Decomposition.
class Solution {
public:
    int longestDecomposition(string text) {
        int N = text.size();
        //dp[i]: max number of palindrome decompositions that s[0:i] + s[len-i:len] can form, not counting the strings between [i+1:len-i-1].
        vector<int> dp(N/2+1, 0);
        int ans = 0;
        for(int r = 0; r < N/2; r++){
            for(int l = 0; l <= r; l++){
                /*
                [l,r] is all possible substrings formed by the former part of text
                for odd N, the middle char is not included
                */
                // cout << l << " " << r << endl;
                //compare [l,r] and [N-r-1,N-l-1]
                //dp[l] != 0: [0,l-1] must be valid so we can construct dp[r+1] upon it
                //dp[0] is always valid
                if(text.substr(l, r-l+1) == text.substr(N-r-1, r-l+1) && 
                   (l == 0 || dp[l] != 0)){
                    //dp[r+1] for s[0:r]
                    //dp[l] for s[0:l-1]
                    //dp[r+1] is for [0,r], and we are calculate it from [0,l-1] and [l,r]
                    //[l,r] is the current substring
                    //dp[l] is for [0,l-1], which is all chars before current substring
                    //dp[r+1] is equal to dp[l] plus current 2 tokens
                    // cout << r << " " << l-1 << " " << text.substr(l, r-l+1) << endl;
                    dp[r+1] = max(dp[r+1], dp[l]+2);
                    //ans: we can find "ans" palindromes from [0:r] and [N-1-r:N-1]
                    //dp[r+1] can be 0 if r is not the end of any palindrome, so we need a max function here
                    // ans = max(ans, dp[l]+2);
                    ans = max(ans, dp[r+1]);
                }
            }
        }
        
        // for(int i = 0; i < dp.size(); i++){
        //     if(dp[i] > 0) cout << "i: " << i << ", " << dp[i] << endl;
        // }
        
        //((N % 2 == 0) && dp[N/2] != 0): the string's length is even and there is a palindrome ends just before the middle point
        return ((N % 2 == 0) && dp[N/2] != 0) ? dp[N/2] : ans+1;
    }
};

//Greedy, brute force
//https://leetcode.com/problems/longest-chunked-palindrome-decomposition/discuss/350560/JavaC%2B%2BPython-Easy-Greedy-with-Prove
//Runtime: 4 ms, faster than 88.52% of C++ online submissions for Longest Chunked Palindrome Decomposition.
//Memory Usage: 10.8 MB, less than 100.00% of C++ online submissions for Longest Chunked Palindrome Decomposition.
//time: O(N) * O(string), space O(N)
class Solution {
public:
    int longestDecomposition(string text) {
        int ans = 0, N = text.size();
        string l = "", r = "";
        for(int i = 0; i < N; i++){
            l += text[i];
            r = text[N-i-1] + r;
            /*
            "ghiabcdefhelloadamhelloabcdefghi"
            the character in the middle can also be processed correctly
            2 ghi
            8 abcdef
            13 hello
            17 adam
            22 hello
            28 abcdef
            31 ghi
            */
            if(l == r){
                // cout << i << " " << l << endl;
                l = "";
                r = "";
                ans++;
            }
        }
        return ans;
    }
};

//Greedy, tail recursion
//https://leetcode.com/problems/longest-chunked-palindrome-decomposition/discuss/350560/JavaC%2B%2BPython-Easy-Greedy-with-Prove
//Runtime: 4 ms, faster than 88.52% of C++ online submissions for Longest Chunked Palindrome Decomposition.
//Memory Usage: 10.7 MB, less than 100.00% of C++ online submissions for Longest Chunked Palindrome Decomposition.
class Solution {
public:
    int longestDecomposition(string text, int res = 0) {
        int n = text.length();
        //l is 1-based
        for (int l = 1; l <= n / 2; ++l){
            //this if is just for speed up
            if (text[0] == text[n - l] && text[l - 1] == text[n - 1]){
                if (text.substr(0, l) == text.substr(n - l)){
                    // cout << l << " " << text.substr(0, l) << endl;
                    //remove current palindrome from text
                    return longestDecomposition(text.substr(l, n - l - l), res + 2);
                }
            }
        }
        /*
        the recursion ends when:
        1. we cannot find any palindrome for text(res + 1)
        2. text's length is 0(res)
        */
        // cout << "n: " << n << endl;
        return n ? res + 1 : res;
    }
};
