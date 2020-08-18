//KMP
//https://gist.github.com/hsinewu/44a1ce38a1baf47893922e3f54807713
//Runtime: 12 ms, faster than 25.32% of C++ online submissions for Implement strStr().
//Memory Usage: 7 MB, less than 100.00% of C++ online submissions for Implement strStr().
class Solution {
public:
    vector<int> getTable(string& pattern){
        vector<int> next(pattern.size(), -1);

        for(int r = 1, l = -1; r < pattern.size(); r++) {
            /*
            if l is -1, we compare from the start of pattern
            */
            /*
            compare pattern[l+1] and pattern[r],
            if they are different, 
            we go back to compare next[l]+1 with r
            */
            while(l != -1 && pattern[l+1] != pattern[r]){
                l = next[l];
            }

            // assert( l == -1 || pattern[l+1] == pattern[r]);
            if( pattern[l+1] == pattern[r]){
                /*
                pattern[?:l+1] and patter[?:r] are the same substring,
                when next time we fail to match pattern[r+1],
                we will fallback to l+2
                
                "next" table stores the end position of the last same substring
                */
                next[r] = l+1;
                l++;
            }
        }

        return next;
    };
    
    int KMPSearch(string& text, string& pattern, vector<int>& next){
        int tail = -1;
        
        for(int i = 0; i < text.size(); i++){
            /*
            if tail == -1, that means we will match from the start of "pattern"
            */
            while(tail != -1 && text[i] != pattern[tail+1]){
                /*
                if tail+1 and i don't match, we then fall back to compare former part of "pattern" to current part of "text"
                */
                tail = next[tail];
            }

            if(text[i] == pattern[tail+1]){
                tail++;
            }
            //we can consider tail as the current matched length

            if( tail == pattern.size()-1){
                return i - tail;
            }
        }
        
        return -1;
    };
    
    int strStr(string haystack, string needle) {
        if(needle == "") return 0;
        int i = 0, j = 0;
        
        vector<int> next = getTable(needle);
        
        // for(int i = 0; i < next.size(); i++){
        //     cout << next[i];
        // }
        // cout << endl;
        
        return KMPSearch(haystack, needle, next);
    }
};

//Brute force
//https://leetcode.com/problems/implement-strstr/discuss/12807/Elegant-Java-solution
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Implement strStr().
//Memory Usage: 7 MB, less than 100.00% of C++ online submissions for Implement strStr().
class Solution {
public:
    int strStr(string haystack, string needle) {
        if(needle.size() == 0) return 0;
        //i + max possible value of j should less than haystack.size()
        for(int i = 0; i + needle.size() - 1 < haystack.size(); i++){
            //break and use next i when we encounter mismatch
            for(int j = 0; j < needle.size() && haystack[i+j] == needle[j]; j++){
                //we can match to the end of needle
                if(j == needle.size()-1) return i;
            }
        }
        
        return -1;
    }
};

//KMP
//https://leetcode.com/problems/implement-strstr/discuss/12956/C%2B%2B-Brute-Force-and-KMP
//https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
//Runtime: 36 ms, faster than 20.93% of C++ online submissions for Implement strStr().
//Memory Usage: 7 MB, less than 100.00% of C++ online submissions for Implement strStr().
class Solution {
public:
    vector<int> computeLPSArray(string& pattern){
        int n = pattern.size();
        //longest proper prefix (also as proper suffix)'s length
        vector<int> lps(n, 0);
        
        for(int i = 1, len = 0; i < n; /*no i++ here!*/){
            if(pattern[i] == pattern[len]){
                len++; //increase proper prefix's length
                lps[i] = len; //record it into the table
                i++; //move forward i
            }else if(len > 0){
                /*
                fallback, we look up in lps to find a shorter prefix,
                which has length lps[len-1](we name it as x).
                From here, we know pattern[0:x-1] equals to pattern[i-x:i-1]
                so we can start the comparison from lps[len-1](x).
                */
                len = lps[len-1];
                //not increment i here!
            }else{
                //len = 0 now
                lps[i] = len;
                //we cannot fallback anymore, so we have nothing but to increase i
                i++;
            }
        }
        
        return lps;
    };
    
    int KMPSearch(string& text, string& pattern){
        int m = text.size(), n = pattern.size();
        if(n == 0) return 0;
        vector<int> lps = computeLPSArray(pattern);
        
        // for(int i = 0; i < lps.size(); i++){
        //     cout << lps[i];
        // }
        // cout << endl;
        
        for (int i = 0, j = 0; i < m;) {
            cout << i << " " << j << endl;
            if (text[i] == pattern[j]) { 
                i++, j++;
            }
            //we have found pattern in text!
            if (j == n) {
                /*
                if we want to find all "pattern" in text:
                j = lps[j-1];
                ans.push_back(i-j);
                */
                /*
                i-1 is the end position of matching
                recall that j servers as length of prefix, 
                i-1 - (j-1) is the start of matching
                */
                return i - j;
            }else if (i < m && text[i] != pattern[j]) {
                //i < m: haven't look to the end of "text"
                //text[i] != pattern[j]: need to change i or j
                if(j > 0){
                    //fallback
                    /*
                    we know that text[i-j...i-1] equlas to pattern[0...j-1],
                    and assume lps[j-1] is x, so pattern[0...x-1] equals to pattern[j-x...j-1],
                    text[i-x...i-1] = pattern[j-x...j-1] = pattern[0...x-1],
                    so we can skip the comparison of text[i-x...i-1] and pattern[0...x-1],
                    and start the next comparison from current i and next j = x
                    */
                    j = lps[j-1];
                }else{
                    /*
                    j equals to 0 here, we cannot fallback, 
                    so we have nothing but to increase i
                    */
                    /*
                    in next iteration, 
                    we match next char in text with the start of pattern
                    */
                    i++;
                }
            }
        }
        return -1;
    }
    
    int strStr(string haystack, string needle) {
        int m = haystack.size(), n = needle.size();
        if(n == 0) return 0;
        return KMPSearch(haystack, needle);
    }
};
